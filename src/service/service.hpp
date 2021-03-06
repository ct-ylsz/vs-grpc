//
// Created by ct on 2022/1/4.
//

#include <memory>
#include <mutex>
#include <string>
#include <iostream>
#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "log/log.h"
#include "resclass/request.h"
#include <utils/flie.h>
#include <fcntl.h>
#include <vs.grpc.pb.h>
#include "resclass/tag.h"
#include "utils/config.h"
#include "utils/util.h"
#include "db/dbvs.h"
#include "resclass/tag_data.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using namespace vs;

enum FeatureType {
    Max = 1, Min, Avg, Count = 99
};

class VsServiceImpl final : public VsService::Service {
public:
    static inline std::shared_ptr<VsServiceImpl> ptr_ = nullptr;
    static inline std::mutex m_mutex_ = std::mutex();
    Logger *log_;
    std::string address_;
    std::string ip_;
    std::string port_;
    std::string log_path_;
    std::string config_path_;
    std::string proc_name_;
public:
    static std::shared_ptr<VsServiceImpl> GetInstance() {
        if (ptr_ == nullptr) {
            std::lock_guard<std::mutex> lk(m_mutex_);
            if (ptr_ == nullptr) {
                ptr_ = std::shared_ptr<VsServiceImpl>(new VsServiceImpl);
            }
        }
        return ptr_;
    }

private:
    VsServiceImpl() {
        log_ = new Logger();
    }

public:
    ~VsServiceImpl() override {
        delete log_;
    }

    [[nodiscard]] int configSetInternal(google::protobuf::Map<std::string, std::string> kvs) const {
        if (kvs.empty()) {
            log_->Error((boost::format("kvs empty")).str());
            return -1;
        }

        auto path = kvs["db_config_path"];
        if (boost::filesystem::is_regular_file(path + "VeStore.ini")) {
//            log_->Warn((boost::format("config is already exist")).str());
            return 0;
        }


        std::map<std::string, std::vector<Kv>> config;
        for (auto &kv: kvs) {
            std::vector<std::string> dest;
            boost::split(dest, kv.first, boost::is_any_of("."), boost::token_compress_on);
            if (dest.size() == 2) {
                Kv k;
                k.key_ = dest[1];
                k.value_ = kv.second;
                config[dest[0]].push_back(k);
            }
        }

        if (config.empty()) {
            log_->Error(
                    R"(configInfo is empty)");
            return -2;
        }
        std::ofstream f;
        f.open(path + "VeStore.ini", std::ios::out);
        for (auto &c: config) {
            f << "[" + c.first << "]" << std::endl;
            for (auto &i: c.second) {
                f << i.key_ + " = " + i.value_ << std::endl;
            }
        }
        f.close();
        return 0;
    }

    // ????????????
    Status TagListGet(ServerContext *context, const TagListGetReq *request, TagListGetResp *response) override {
        log_->Debug((boost::format("TagListGet:%1%") % request->Utf8DebugString()).str());
        // ????kvs ????????
        if (request->kvs().kvs_size() == 0) {
            log_->Error("request->kvs().kvs_size() == 0");
            return {StatusCode::INVALID_ARGUMENT, "kvs is empty"};
        }

//        auto err_c = configSetInternal(request->kvs().kvs());
//        if (err_c != 0) {
//            log_->Error("configSetInternal(kvs);");
//            return {StatusCode(err_c), "write config_file failed"};
//        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        auto *tags = new std::vector<TagInfo>();
        if (request->page() >= 0 && request->size() > 0) {
            if (request->size() > 2000) {
                log_->Error((boost::format("size is too large ")).str());
                delete tags;
                return {StatusCode::INVALID_ARGUMENT, "size is too large"};
            }

            auto begin = (request->page() * request->size());
            long size = request->size();

            err = DbVs::TagListByCount(begin, tags, size);
            if (err.err_code != 0) {
                log_->Error((boost::format("get tagList failed  err_code %1%: err_msg %2%") % err.err_code %
                             err.err_msg).str());
                if (!tags->empty()) {
                    tags->clear();
                }
                delete tags;
                return {StatusCode(err.err_code), "get taglist failed"};
            }
        } else {
            err = DbVs::TagListAll(tags);
            log_->Debug((boost::format("get TagsNameGet err_code %1%:%2%") % err.err_code % err.err_msg).str());
            if (err.err_code != 0) {
                log_->Error((boost::format("taglist get all err_code %1%:%2%") % err.err_code % err.err_msg).str());
                if (!tags->empty()) {
                    tags->clear();
                }
                delete tags;
                return {StatusCode(err.err_code), "get taglist failed"};
            }
        }

        log_->Info((boost::format("get data size %1%") % tags->size()).str());
        TagsInfo tagsIn;


        for (auto &tag: *tags) {
            auto x = response->add_tags();
            std::map<std::string, std::string> m_map;
            m_map["unit"] = tag.unit;
            m_map["max"] = std::to_string(tag.max);
            m_map["min"] = std::to_string(tag.min);
            m_map["desc"] = tag.desc;
            m_map["name"] = tag.name;
            google::protobuf::Map<std::string, std::string> m(m_map.begin(), m_map.end());
            x->mutable_infos()->swap(m);
        }
        if (!tags->empty()) {
            tags->clear();
        }
        delete tags;
        return Status::OK;
    }

    // ??????????
    Status TagValuesGet(ServerContext *context, const TagValuesGetReq *request, TagValuesGetResp *response) override {
        log_->Debug((boost::format("TagValuesGet:%1%") % request->Utf8DebugString()).str());
        auto start = request->head().start();
        auto end = request->head().end();
        auto tag_name = request->head().tagname();

        if (start > end || start <= 0 || end <= 0 || tag_name.empty() || request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        // ????kvs ????????
        if (request->kvs().kvs_size() == 0) {
            log_->Error("request->kvs().kvs_size() == 0");
            return {StatusCode::INVALID_ARGUMENT, "request->kvs().kvs_size() == 0"};
        }

//        auto err_c = configSetInternal(request->kvs().kvs());
//        if (err_c != 0) {
//            log_->Error("configSetInternal(kvs);");
//            return {StatusCode(err_c), "write config_file failed"};
//        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long count = 1024;
        auto *dataF = new TagDataF();
        ReadHiDataRequest req;
        strcpy(req.pointName, tag_name.c_str());
        req.stTime = start;
        req.enTime = end;
        req.tPeriod = request->head().period();
        req.reqType = request->head().reqtype();

        while (count == 1024 && req.stTime <= req.enTime) {
            auto *data2 = new std::vector<TagData>();
            err = DbVs::TagValuesGet(req, count, data2);
            if (err.err_code != 0) {
                response->mutable_err()->set_errcode(err.err_code);
                response->mutable_err()->set_errmsg(err.err_msg);
                return Status::OK;
            }
            if (!data2->empty()) {
                log_->Info((boost::format("get count size %1%") % data2->size()).str());
                TagDataInfo dataInfo;
                for (auto &d: *data2) {
                    dataInfo.status_ = d.status;
                    dataInfo.ts_ = d.time;
                    dataInfo.value_ = d.value;
                    dataF->tags_.push_back(dataInfo);
                }
                req.stTime = data2->back().time + 1;
                data2->clear();
                delete data2;
            } else {
                log_->Info((boost::format("query no data")).str());
                delete data2;
                break;
            }
        }


        for (auto &value: dataF->tags_) {
            auto t = response->add_values()->mutable_valuemap();
            (*t)["ts"] = std::to_string(value.ts_);
            (*t)["value"] = std::to_string(value.value_);
            (*t)["status"] = std::to_string(value.status_);
        }

        delete dataF;
        return Status::OK;
    }

    // ??????????????
    Status TagValuesByCountGet(ServerContext *context, const TagValuesByCountGetReq *request,
                               TagValuesByCountGetResp *response) override {
        log_->Debug((boost::format("TagValuesByCountGet:%1%") % request->Utf8DebugString()).str());
        auto start = request->head().start();
        auto end = request->head().end();
        auto tag_name = request->head().tagname();

        if (start > end || start <= 0 || end <= 0 || tag_name.empty() || request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

//        auto err_c = configSetInternal(request->kvs().kvs());
//        if (err_c != 0) {
//            log_->Error("configSetInternal(kvs);");
//            return {StatusCode(err_c), "write config_file failed"};
//        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long count = 1024;
        long tmp_count = 0;
        auto *dataF = new TagDataF();

        ReadHiDataRequest req;
        strcpy(req.pointName, tag_name.c_str());
        req.stTime = start;
        req.enTime = end;
        req.tPeriod = request->head().period();
        req.reqType = request->head().reqtype();

        while (count == 1024 && req.stTime <= req.enTime) {
            auto *data2 = new std::vector<TagData>();
            err = DbVs::TagValuesGet(req, count, data2);
            if (err.err_code != 0) {
                response->mutable_err()->set_errcode(err.err_code);
                response->mutable_err()->set_errmsg(err.err_msg);
                return Status::OK;
            }
            if (!data2->empty()) {
                log_->Info((boost::format("get count size %1%") % data2->size()).str());
                tmp_count += count;
                TagDataInfo dataInfo;
                if (request->count() <= tmp_count) {
                    long x = request->count() - (tmp_count - count);
                    for (int i = 0; i < x; i++) {
                        dataInfo.status_ = (*data2)[i].status;
                        dataInfo.ts_ = (*data2)[i].time;
                        dataInfo.value_ = (*data2)[i].value;
                        dataF->tags_.push_back(dataInfo);
                    }
                    break;
                } else {
                    for (auto &d: *data2) {
                        dataInfo.status_ = d.status;
                        dataInfo.ts_ = d.time;
                        dataInfo.value_ = d.value;
                        dataF->tags_.push_back(dataInfo);
                    }
                }
                req.stTime = data2->back().time + 1;
                data2->clear();
                delete data2;
            } else {
                log_->Info((boost::format("query no data")).str());
                delete data2;
                break;
            }
        }

        for (auto &value: dataF->tags_) {
            auto t = response->add_values()->mutable_valuemap();
            (*t)["ts"] = std::to_string(value.ts_);
            (*t)["value"] = std::to_string(value.value_);
            (*t)["status"] = std::to_string(value.status_);
        }

        delete dataF;
        return Status::OK;
    }

    // ??????????
    Status
    TagFeatureGet(ServerContext *context, const TagFeatureGetReq *request, TagFeatureGetResp *response) override {
        log_->Debug((boost::format("TagFeatureGet:%1%") % request->Utf8DebugString()).str());
        long start = request->start();
        long end = request->end();
        const auto &name = request->tagname();

        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

//        auto err_c = configSetInternal(request->kvs().kvs());
//        if (err_c != 0) {
//            log_->Error(boost::str(boost::format("configSetInternal(kvs): %1%") % err_c));
//            return {StatusCode(err_c), "write config_file failed"};
//        }

        char dll_path[128];
        char config_path[128];

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);

        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        auto it = response->mutable_feats();
        TagData feat;
        VsValue info;
        long tmp_count = 0;
        long count = 1024;
        for (int i: request->verifies()) {
            switch (i) {
                case Max:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["max"] = info;
                    }
                    continue;
                case Min:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["min"] = info;
                    }
                    continue;
                case Avg:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["avg"] = info;
                    }
                    continue;
                case Count:
                    ReadHiDataRequest req;
                    strcpy(req.pointName, name.c_str());
                    req.stTime = start;
                    req.enTime = end;
                    while (count == 1024 && req.stTime < req.enTime) {
                        auto *data2 = new std::vector<TagData>();
                        err = DbVs::TagValuesGet(req, count, data2);
                        if (err.err_code != 0) {
                            log_->Error((boost::format("get value err.err_code %1%") % err.err_code).str());
                            break;
                        }
                        if (!data2->empty()) {
                            log_->Info((boost::format("get count size %1%") % data2->size()).str());
                            tmp_count += count; //??????
                            req.stTime = data2->back().time + 1;
                            delete data2;
                        } else {
                            log_->Info((boost::format("query no data")).str());
                            tmp_count += count;
                            delete data2;
                        }
                    }
                    info.set_value(tmp_count);
                    info.set_status(100);
                    (*it)["count"] = info;
                    continue;
                default:
                    log_->Error((boost::format("unsupported types ")).str());
                    continue;
            }
        }
        return Status::OK;
    }

    // ??????????
    Status
    TagTimeSection(ServerContext *context, const TagTimeSectionReq *request, TagTimeSectionResp *response) override {
        log_->Debug((boost::format("TagTimeSection:%1%") % request->Utf8DebugString()).str());
        long start = request->start();
        long end = request->end();
        const auto &name = request->tagname();

        if (request->kvs().kvs().empty() || request->tagname().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

//        auto err_c = configSetInternal(request->kvs().kvs());
//        if (err_c != 0) {
//            log_->Error("configSetInternal(kvs);");
//            return {StatusCode(err_c), "write config_file failed"};
//        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);

        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long count = 1;
        TagData da;
        auto *data1 = new std::vector<TagData>();
        err = DbVs::TagValuesGet(name, (long) start, (long) end, count, data1);
        if (err.err_code != 0) {
            DbVs::DbReleaseConnect();
            if (count == 0) {
                response->set_start(0);
                response->set_end(0);
                return Status::OK;
            }
            response->mutable_err()->set_errcode(err.err_code);
            response->mutable_err()->set_errmsg(err.err_msg);
            log_->Error((boost::format("get time section failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), err.err_msg};
        }
        if (!data1->empty()) {
            log_->Info((boost::format("get count size %1%") % data1->size()).str());
            if (start < data1->front().time) {
                start = data1->front().time;
            }
            data1->clear();
            delete data1;
        } else {
            log_->Info((boost::format("query no data")).str());
            delete data1;
        }

        err = DbVs::TagRealTimeDataGetByName(name.c_str(), &da);
        if (err.err_code != 0) {
            DbVs::DbReleaseConnect();
            log_->Error(
                    (boost::format("TagRealTimeDataGetByName failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "TagRealTimeDataGetByNamefailed"};
        }

        response->set_start(start);
        response->set_end(da.time);
        return Status::OK;
    }

    //Ping ??????
    Status DbPing(ServerContext *context, const DbPingReq *request, DbPingResp *response) override {
        log_->Debug((boost::format("DbPing:%1%") % request->Utf8DebugString()).str());

        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long size = 1;
        auto *tags = new std::vector<TagInfo>();
        err = DbVs::TagListByCount(0, tags, size);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        response->set_flag(true);
        return Status::OK;
    }

    // ????????????????
    Status TagCountByRangeGet(ServerContext *context, const TagCountByRangeGetReq *request,
                              TagCountByRangeGetResp *response) override {
        log_->Debug((boost::format("TagCountByRangeGet:%1%") % request->Utf8DebugString()).str());
        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long start = request->start();
        auto end = request->end();
        const auto &name = request->tagname();
        long tmp_count = 0;
        long count = 1024;
        while (count == 1024 && start < end) {
            auto *data1 = new std::vector<TagData>();
            err = DbVs::TagValuesGet(name, (long) start, (long) end, count, data1);
            if (err.err_code != 0) {
                response->mutable_err()->set_errcode(err.err_code);
                response->mutable_err()->set_errmsg(err.err_msg);
                return {StatusCode(err.err_code), err.err_msg};
            }
            if (!data1->empty()) {
                log_->Info((boost::format("get count size %1%") % data1->size()).str());
                tmp_count += count; //??????
                start = data1->back().time + 1;
                data1->clear();
                delete data1;
            } else {
                log_->Info((boost::format("query no data")).str());
                tmp_count += count;
                delete data1;
            }
        }
        response->set_count(tmp_count);
        return Status::OK;
    }

    // ????????
    Status ServiceStop(ServerContext *context, const ServiceStopReq *request, ServiceStopResp *response) override {
        log_->Debug((boost::format("ServiceStop:%1%") % request->DebugString()).str());
        boost::thread th([]() {
            DbVs::DbReleaseConnect();
            Sleep(10000);
            exit(0);
        });//????????????????????????
        return Status::OK;
    }

    // ??????????
    Status TagSnapshotValue(ServerContext *context, const TagSnapshotValueReq *request,
                            TagSnapshotValueResp *response) override {
        log_->Debug((boost::format("TagSnapshotValue:%1%") % request->DebugString()).str());
        auto start = request->start();
        auto end = request->end();
        auto tag_name = request->tagname();
        if (tag_name.empty() || request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }


        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");
        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        TagData value;
        err = DbVs::TagRealTimeDataGetByName(tag_name.c_str(), &value);
        if (err.err_code != 0) {
            log_->Error((boost::format("get snapshot failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "get snapshot failed"};
        }

        auto t = response->mutable_values()->mutable_valuemap();
        (*t)["ts"] = std::to_string(value.time);
        (*t)["value"] = std::to_string(value.value);
        (*t)["status"] = std::to_string(value.status);
        return Status::OK;
    }

    // ??????????
    Status TagFractureSectionGet(ServerContext *context, const TagFractureSectionGetReq *request,
                                 TagFractureSectionGetResp *response) override {
        log_->Debug((boost::format("TagFractureSectionGet:%1%") % request->Utf8DebugString()).str());
        long count = request->count();
        if (request->head().start() > request->head().end() || request->head().start() <= 0 ||
            request->head().end() <= 0 || request->head().tagname().empty() || request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % request->head().start() % request->head().end() %
                         request->head().tagname()).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }


        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        auto *dataF = new TagDataF();
        ReadHiDataRequest req;
        strcpy(req.pointName, request->head().tagname().c_str());
        req.stTime = request->head().start();
        req.enTime = request->head().end();
        req.tPeriod = request->head().period();
        req.reqType = request->head().reqtype();
        while (count == 1024 && req.stTime < req.enTime) {
            auto *data2 = new std::vector<TagData>();
            auto err2 = DbVs::TagValuesGet(req, count, data2);
            if (err.err_code != 0) {
                response->mutable_err()->set_errcode(err.err_code);
                response->mutable_err()->set_errmsg(err.err_msg);
                return {StatusCode(err.err_code), err.err_msg};
            }
            if (!data2->empty()) {
                log_->Info((boost::format("get count size %1%") % data2->size()).str());
                TagDataInfo dataInfo;
                for (auto &d: *data2) {
                    dataInfo.status_ = d.status;
                    dataInfo.ts_ = d.time;
                    dataInfo.value_ = d.value;
                    dataF->tags_.push_back(dataInfo);
                }
                req.stTime = data2->back().time + 1;
                data2->clear();
                delete data2;
            } else {
                log_->Info((boost::format("query no data")).str());
                delete data2;
                break;
            }
        }


        for (auto &value: dataF->tags_) {
            auto t = response->add_values()->mutable_valuemap();
            (*t)["ts"] = std::to_string(value.ts_);
            (*t)["value"] = std::to_string(value.value_);
            (*t)["status"] = std::to_string(value.status_);
        }
        delete dataF;
        return Status::OK;
    }

    //Ping ????????
    Status TagDescGet(ServerContext *context, const TagDescGetReq *request, TagDescGetResp *response) override {
        log_->Debug((boost::format("TagDescGet:%1%") % request->Utf8DebugString()).str());
        if (request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%") % "arg is not valid").str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        TagInfo tagInfo;
        char *name = (char *) malloc(256);
        strcpy(name, request->tagname().c_str());
        err = DbVs::TagDescInfoGet(name, &tagInfo);
        free(name);
        if (err.err_code != 0) {
            log_->Error((boost::format("get desc info faield :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), err.err_msg};
        }

        auto it = response->mutable_desc();
        (*it)["desc"] = tagInfo.desc;
        (*it)["name"] = tagInfo.name;
        (*it)["min"] = std::to_string(tagInfo.min);
        (*it)["max"] = std::to_string(tagInfo.max);
        (*it)["unit"] = tagInfo.unit;
        return Status::OK;
    }

    //TagAppendRTTagDataByBatch ????????????????
    Status TagAppendRTTagDataByBatch(ServerContext *context, const TagAppendRTTagDataByBatchReq *request,
                                     TagAppendRTTagDataByBatchResp *response) override {
        log_->Debug((boost::format("TagAppendRTTagDataByBatch:%1%") % request->Utf8DebugString()).str());
        if (request->kvs().kvs().empty()) {
            log_->Error((boost::format("TagAppendRTTagDataByBatch:%1%") % "arg is not valid").str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }
        if (request->data().empty()) {
            log_->Error((boost::format("TagAppendRTTagDataByBatch:%1%") % "arg is not valid").str());
            return {StatusCode::INVALID_ARGUMENT, "no data to write"};
        }

        auto err_c = configSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("configSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char dll_path[128];
        char config_path[128];
        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }


        auto *data = (InsertData_struct *) malloc(request->data().size());
        for (int i = 0; i < request->data().size(); i++) {
            data[i].value = request->data()[i].value();
            data[i].type = request->data()[i].type();
            strcpy(data[i].pointName, request->data()[i].tagname().c_str());
            data[i].status = request->data()[i].status();
            data[i].time = request->data()[i].time();
        }
        err = DbVs::TagDataInsert(data, request->data().size());
        if (err.err_code != 0) {
            log_->Error((boost::format("get desc info faield :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), err.err_msg};
        }

        for (int i = 0; i < request->data().size(); i++) {
            auto x = response->add_data();
            x->set_tagname(data[i].pointName);
            x->set_type(data[i].type);
            x->set_status(data[i].status);
            x->set_value(data[i].value);
            x->set_time(data[i].time);
        }
        free(data);
        return Status::OK;
    }


    void Run() {
        if (ip_.empty() || port_.empty()) {
            log_->Error((boost::format("please input correct address :%1%-%2%") % ip_ % port_).str());
            return;
        }

        Config c;
        c.ip_ = ip_;
        c.port_ = port_;
        c.config_path_ = config_path_;
//        if (boost::filesystem::is_regular_file(c.config_path_)) {
//            ParseYamlConfig(c.config_path_, &c);
//        }

        std::string server_address((boost::format("%1%:%2%") % c.ip_ % c.port_).str());
        DbVs::Init("./");
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(this);
        builder.SetMaxMessageSize(500 * 1024 * 1024);
        log_->Info((boost::format("Server listening on:%1%-%2%") % c.ip_ % c.port_).str());
        std::unique_ptr<Server> server(builder.BuildAndStart());
        server->Wait();
    }
};
