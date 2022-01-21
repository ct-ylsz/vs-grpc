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
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "log/log.h"
#include "error/error.h"
#include "resclass/request.h"
#include <utils/flie.h>
#include <fcntl.h>
#include <vs.grpc.pb.h>
#include "resclass/tag.h"
#include "utils/config.h"
#include "resclass/pi_config.h"
#include "utils/util.h"
#include "resclass/request.h"
#include "db/dbvs.h"
#include "resclass/tag_data.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using namespace vs;

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

    [[nodiscard]] int ConfigSetInternal(google::protobuf::Map<std::string, std::string> kvs) const {
        if (kvs.empty()) {
            log_->Error((boost::format("kvs empty")).str());
            return -1;
        }

        auto path = kvs["db_config_path"];
        std::map<std::string, std::vector<Kv>> config;
        for (auto &kv: kvs) {
            std::vector<std::string> dest;
            boost::split(dest, kv.first, boost::is_any_of("."),
                         boost::token_compress_on);//如果此处使用boost::token_compress_off
            if (dest.size() == 2) {
                Kv k;
                k.key_ = dest[1];
                k.value_ = kv.second;
                config[dest[0]].push_back(k);
            }
        }

        if (config.empty()) {
            log_->Error(
                    R"(boost::filesystem::is_regular_file(inline_task.block_["target_file"] + ".tmp") is already has )");
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

    // 获取标签列表
    Status TagListGet(ServerContext *context, const TagListGetReq *request, TagListGetResp *response) override {
        log_->Info((boost::format("TagListGet:%1%") % request->DebugString()).str());
        // 检查kvs 是否输入
        if (request->kvs().kvs_size() == 0) {
            log_->Error("request->kvs().kvs_size() == 0");
            return {StatusCode::INVALID_ARGUMENT, "addr or username is empty"};
        }

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        auto *tags = new std::vector<TagInfo>();
        if (request->page() > 0 && request->size() > 0) {
            if (request->size() > 2000) {
                log_->Error((boost::format("size is too large ")).str());
                delete tags;
                return {StatusCode::INVALID_ARGUMENT, "size is too large"};
            }

            auto begin = (request->page() * request->size());
            long size = request->size();

            err = DbVs::TagListByCount(begin, tags, size);
            // DbVs::DbReleaseConnect();
            if (err.err_code != 0) {
//                DbVs::DbReleaseConnect();
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
//            DbVs::DbReleaseConnect();
            log_->Info((boost::format("get TagsNameGet err_code %1%:%2%") % err.err_code % err.err_msg).str());
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
            x->mutable_info()->swap(m);
            x->mutable_fileds()->Add()->set_columnname("ts");
            x->mutable_fileds()->Add()->set_columnname("value");
            x->mutable_fileds()->Add()->set_columnname("status");
        }
        if (!tags->empty()) {
            tags->clear();
        }
        delete tags;
        return Status::OK;
    }

    // 获取所有值
    Status TagValuesGet(ServerContext *context, const TagValuesGetReq *request, TagValuesGetResp *response) override {
        log_->Info((boost::format("TagValuesGet:%1%") % request->Utf8DebugString()).str());
        auto start = request->start();
        auto end = request->end();
        auto tag_name = request->tagname();
        const auto &addr = request->addr();
        const auto &username = request->username();
        const auto &password = request->password();
        if (start > end || start <= 0 || end <= 0 || tag_name.empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        // 检查kvs 是否输入
        if (request->kvs().kvs_size() == 0) {
            log_->Error("request->kvs().kvs_size() == 0");
            return {StatusCode::INVALID_ARGUMENT, "addr or username is empty"};
        }

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long count = 1024;
        long start_tmp = 0;
        long end_tmp = 0;
        TagDataF dataF;
        while (count == 1024 && start <= end) {
            auto *data2 = new std::vector<TagData>();
            ReadHiDataRequest req;
            strcpy(req.pointName, tag_name.c_str());
            req.stTime = start;
            req.enTime = end;
            err = DbVs::TagValuesGet(req, count, data2);
            if (err.err_code == 0 && !data2->empty()) {
                log_->Info((boost::format("get count size %1%") % data2->size()).str());
                TagDataInfo dataInfo;
                for (auto &d: *data2) {
                    dataInfo.status_ = d.status;
                    dataInfo.ts_ = d.time;
                    dataInfo.value_ = d.value;
                    dataF.tags_.push_back(dataInfo);
                }
                if (start_tmp == 0) {
                    start_tmp = data2->front().time;
                }
                start = data2->back().time;
                data2->clear();
                delete data2;
            } else {
                if (start_tmp == 0) {
                    start_tmp = request->start();
                }
                if (!data2->empty()) {
                    end_tmp = data2->back().time;
                }
                log_->Info((boost::format("query no data")).str());
                delete data2;
                break;
            }
        }

        //DbVs::DbReleaseConnect();

        for (auto &value: dataF.tags_) {
            auto t = response->add_values()->mutable_valuemap();
            (*t)["ts"] = std::to_string(value.ts_);
            (*t)["value"] = std::to_string(value.value_);
            (*t)["status"] = std::to_string(value.status_);
        }

        return Status::OK;
    }

    // 根据数量获取值
    Status TagValuesByCountGet(ServerContext *context, const TagValuesByCountGetReq *request,
                               TagValuesByCountGetResp *response) override {
        log_->Info((boost::format("TagValuesByCountGet:%1%") % request->Utf8DebugString()).str());
        auto start = request->start();
        auto end = request->end();
        auto tag_name = request->tagname();
        const auto &addr = request->addr();
        const auto &username = request->username();
        const auto &password = request->password();
        if (start > end || start <= 0 || end <= 0 || tag_name.empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }
        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }


        long count = 1024;
//        auto extend = req->extend_obj_;
        long start_tmp = 0;
        long tmp_count = 0;
        TagDataF dataF;
        while (count == 1024 && start <= end) {
            auto *data2 = new std::vector<TagData>();
            ReadHiDataRequest req;
            strcpy(req.pointName, tag_name.c_str());
            req.stTime = start;
            req.enTime = end;
            err = DbVs::TagValuesGet(req, count, data2);
            if (err.err_code == 0 && !data2->empty()) {
                log_->Info((boost::format("get count size %1%") % data2->size()).str());
                tmp_count += count;
                TagDataInfo dataInfo;
                if (start_tmp == 0) {
                    start_tmp = data2->front().time;
                }
                if (request->count() < tmp_count) {
                    long x = request->count() - (tmp_count - count);
                    end = (*data2)[x - 1].time;
                    for (int i = 0; i < x; i++) {
                        dataInfo.status_ = (*data2)[i].status;
                        dataInfo.ts_ = (*data2)[i].time;
                        dataInfo.value_ = (*data2)[i].value;
                        dataF.tags_.push_back(dataInfo);
                    }
                    break;
                } else {
                    for (auto &d: *data2) {
                        dataInfo.status_ = d.status;
                        dataInfo.ts_ = d.time;
                        dataInfo.value_ = d.value;
                        dataF.tags_.push_back(dataInfo);
                    }
                }
                start = data2->back().time + 1;
                data2->clear();
                delete data2;
            } else {
                if (start_tmp == 0) {
                    start_tmp = request->start();
                }
                if (!data2->empty()) {
                    end = data2->back().time;
                }
                log_->Info((boost::format("query no data")).str());
                delete data2;
                break;
            }
        }
        //DbVs::DbReleaseConnect();
        if (end == 0) {
            time_t t;
            time(&t);
            end = t;
        }

        response->set_start(start_tmp);
        response->set_end(end);

        for (auto &value: dataF.tags_) {
            auto t = response->add_values()->mutable_valuemap();
            (*t)["ts"] = std::to_string(value.ts_);
            (*t)["value"] = std::to_string(value.value_);
            (*t)["status"] = std::to_string(value.status_);
        }

        return Status::OK;
    }

    // 获取特征值
    Status
    TagFeatureGet(ServerContext *context, const TagFeatureGetReq *request, TagFeatureGetResp *response) override {
        log_->Info((boost::format("TagFeatureGet:%1%") % request->Utf8DebugString()).str());
        auto start = request->start();
        auto end = request->end();
        const auto &name = request->tagname();

        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error(boost::str(boost::format("ConfigSetInternal(kvs): %1%") % err_c));
            return {StatusCode(err_c), "write config_file failed"};
        }

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
        auto it = response->mutable_feat();
        TagData feat;
        VsValue info;
        long tmp_start = 0;
        long tmp_end = 0;
        long tmp_count = 0;
        long count = 1024;
        for (int i: request->verifies()) {
            switch (i) {
                case 1:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["max"] = info;
                    }
                    continue;
                case 2:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        VsValue info;
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["min"] = info;
                    }
                    continue;
                case 3:
                    err = DbVs::TagGetAggregation(name, start, end, i, end - start, &feat);
                    if (err.err_code == 0) {
                        log_->Info((boost::format("get value %1%") % feat.value).str());
                        info.set_value(feat.value);
                        info.set_status(feat.status);
                        (*it)["avg"] = info;
                    }
                    continue;
                case 99:
                    while (count == 1024 && start < end) {
                        auto *data2 = new std::vector<TagData>();
                        ReadHiDataRequest req;
                        strcpy(req.pointName, name.c_str());
                        req.stTime = start;
                        req.enTime = end;
                        err = DbVs::TagValuesGet(req, count, data2);
                        if (err.err_code == 0 && !data2->empty()) {
                            log_->Info((boost::format("get count size %1%") % data2->size()).str());
                            tmp_count += count; //总数量
                            start = data2->back().time + 1;
                            if (tmp_start == 0) {
                                tmp_start = data2->front().time;
                            }
                            tmp_end = data2->back().time + 1;
                            delete data2;
                        } else {
                            log_->Info((boost::format("query no data")).str());
                            tmp_count += count;
                            delete data2;
                            //DbVs::DbReleaseConnect();
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

        if (tmp_start > 0) {
            response->set_start(tmp_start);
        } else {
            response->set_start(start);
        }
        if (tmp_end > 0) {
            response->set_end(tmp_end);
        } else {
            response->set_start(end);
        }
        return Status::OK;
    }

    // 获取时间段
    Status
    TagTimeSection(ServerContext *context, const TagTimeSectionReq *request, TagTimeSectionResp *response) override {
        log_->Info((boost::format("TagTimeSection:%1%") % request->Utf8DebugString()).str());
        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }
        long start = request->start();
        long end = request->end();
        if (start > end || start <= 0 || end <= 0 || request->tagname().empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % request->tagname()).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        const auto &name = request->tagname();
        long start_tmp = 0;
        long end_tmp = 0;
        long count = 1;
        TagData da;
        auto *data1 = new std::vector<TagData>();
        err = DbVs::TagValuesGet(name, (long) start, (long) end, count, data1);
        if (err.err_code == 0 && !data1->empty()) {
            log_->Info((boost::format("get count size %1%") % data1->size()).str());
            start_tmp = data1->front().time;
            data1->clear();
            delete data1;
            err = DbVs::TagRealTimeDataGetByName(name.c_str(), &da);
            if (err.err_code != 0) {
                //DbVs::DbReleaseConnect();
                log_->Error(
                        (boost::format("TagRealTimeDataGetByName failed :%1%:%2%") % err.err_code % err.err_msg).str());
                return {StatusCode(err.err_code), "TagRealTimeDataGetByNamefailed"};
            }
        } else {
            start_tmp = request->start();
            log_->Info((boost::format("query no data")).str());
            delete data1;
            //DbVs::DbReleaseConnect();
        }
        if (da.time > 0) {
            end_tmp = da.time;
        }

        response->set_start(start_tmp);
        response->set_end(end_tmp);
        return Status::OK;
    }

    //Ping 数据库
    Status DbPing(ServerContext *context, const DbPingReq *request, DbPingResp *response) override {
        log_->Info((boost::format("DbPing:%1%") % request->Utf8DebugString()).str());

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        long size = 1;
        auto *tags = new std::vector<TagInfo>();
        err = DbVs::TagListByCount(0, tags, size);
        //DbVs::DbReleaseConnect();
        if (err.err_code != 0) {
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        response->set_flag(true);
        return Status::OK;
    }

    // 获取范围内值数量
    Status TagCountByRangeGet(ServerContext *context, const TagCountByRangeGetReq *request,
                              TagCountByRangeGetResp *response) override {
        log_->Info((boost::format("TagCountByRangeGet:%1%") % request->Utf8DebugString()).str());

        if (request->kvs().kvs().empty()) {
            log_->Error(boost::str(boost::format("%1%") % "arg is not valid"));
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }
        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
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
            if (err.err_code == 0 && !data1->empty()) {
                log_->Info((boost::format("get count size %1%") % data1->size()).str());
                tmp_count += count; //总数量
                start = data1->back().time;
                data1->clear();
                delete data1;
            } else {
                log_->Info((boost::format("query no data")).str());
                tmp_count += count;
                delete data1;
                //DbVs::DbReleaseConnect();
            }
        }
        response->set_count(tmp_count);
        return Status::OK;
    }

    // 停止服务
    Status ServiceStop(ServerContext *context, const ServiceStopReq *request, ServiceStopResp *response) override {
        log_->Info((boost::format("ServiceStop:%1%") % request->Utf8DebugString()).str());
        DbVs::DbReleaseConnect();
        exit(0);
        return Status::OK;
    }

    // 获取快照值
    Status TagSnapshotValue(ServerContext *context, const TagSnapshotValueReq *request,
                            TagSnapshotValueResp *response) override {
        log_->Info((boost::format("TagSnapshotValue:%1%") % request->Utf8DebugString()).str());
        auto start = request->start();
        auto end = request->end();
        auto tag_name = request->tagname();
        const auto &addr = request->addr();
        const auto &username = request->username();
        const auto &password = request->password();
        if (start > end || start < 0 || end < 0 || tag_name.empty()) {
            log_->Error((boost::format("TagValuesGet:%1%:%2%:%3%") % start % end % tag_name).str());
            return {StatusCode::INVALID_ARGUMENT, "arg is not valid"};
        }

        // 检查kvs 是否输入
        if (request->kvs().kvs_size() == 0) {
            log_->Error("request->kvs().kvs_size() == 0");
            return {StatusCode::INVALID_ARGUMENT, "addr or username is empty"};
        }

        auto err_c = ConfigSetInternal(request->kvs().kvs());
        if (err_c != 0) {
            log_->Error("ConfigSetInternal(kvs);");
            return {StatusCode(err_c), "write config_file failed"};
        }

        char *dll_path = (char *) malloc(128);
        char *config_path = (char *) malloc(128);

        strcpy(dll_path, "./");
        strcpy(config_path, "./");

        auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
        free(dll_path);
        free(config_path);

        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "connect database failed"};
        }

        TagData value;
        err = DbVs::TagRealTimeDataGetByName(tag_name.c_str(), &value);
        if (err.err_code != 0) {
            //DbVs::DbReleaseConnect();
            log_->Error((boost::format("get snapshot failed :%1%:%2%") % err.err_code % err.err_msg).str());
            return {StatusCode(err.err_code), "get snapshot failed"};
        }

        //DbVs::DbReleaseConnect();
        auto t = response->mutable_values()->mutable_valuemap();
        (*t)["ts"] = std::to_string(value.time);
        (*t)["value"] = std::to_string(value.value);
        (*t)["status"] = std::to_string(value.status);
        return Status::OK;
    }

    void Run() {
        if (ip_.empty() || port_.empty()) {
            log_->Error((boost::format("please input correct address :%1%-%2%") % ip_ % port_).str());
            return;
        }

        PiConfig c;
        c.ip_ = ip_;
        c.port_ = port_;
        c.config_path_ = config_path_;
        if (boost::filesystem::is_regular_file(c.config_path_) || boost::filesystem::is_regular_file(c.config_path_)) {
            ParseYamlConfig(c.config_path_, &c);
        }

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