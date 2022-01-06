//
// Created by ct on 2021/11/2.
//
#include "resclass/request.h"

void RequestCollectData::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("tasks") && dom["tasks"].IsArray()) {
            const rapidjson::Value &array = dom["tasks"];
            size_t len = array.Size();
            for (size_t i = 0; i < len; i++) {
                const rapidjson::Value &object = array[i];
                Task t;
                //为防止类型不匹配，一般会添加类型校验
                if (object.IsObject()) {
                    if (object.HasMember("source_info") && object["source_info"].IsObject()) {
                        auto source = object["source_info"].GetObject();
                        t.source_info_.SourceInfo::GetObj(source);
                        if (source.HasMember("tag") && source["tag"].IsObject()) {
                            auto tag = source["tag"].GetObject();
                            t.source_info_.Tag::GetObj(tag);
                        }
                    }
                    if (object.HasMember("status_file_path") && object["status_file_path"].IsString()) {
                        t.status_file_path_ = object["status_file_path"].GetString();
                    }
                    if (object.HasMember("task_schedule_file_path") && object["task_schedule_file_path"].IsString()) {
                        t.task_schedule_file_path_ = object["task_schedule_file_path"].GetString();
                    }
                    if (object.HasMember("eigenvalue") && object["eigenvalue"].IsObject()) {
                        auto eigenvalue = object["eigenvalue"].GetObject();
                        t.eigenvalue_.GetObj(eigenvalue);
                    }
                    if (object.HasMember("task_path") && object["task_path"].IsObject()) {
                        auto task_path = object["task_path"].GetObject();
                        t.task_path_.GetObj(task_path);
                    }
                }
                tasks_.inline_tasks_.push_back(t);
            }
        }
    }
}

void RequestDesc::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("arrange") && dom["arrange"].IsObject()) {
            const rapidjson::Value &object = dom["arrange"].GetObject();
            if (object.HasMember("tag") && object["tag"].IsObject()) {
                auto tag = object["tag"].GetObject();
                arrange_.Tag::GetObj(tag);
            }
        }
        if (dom.HasMember("time_start") && dom["time_start"].IsInt64()) {
            time_start_ = dom["time_start"].GetInt64();
        }
        if (dom.HasMember("time_end") && dom["time_end"].IsInt64()) {
            time_end_ = dom["time_end"].GetInt64();
        }
    }
}

void RequestTimeSection::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("dll_path") && dom["dll_path"].IsString()) {
            dll_path_ = dom["dll_path"].GetString();
        }
        if (dom.HasMember("config_path") && dom["config_path"].IsString()) {
            config_path_ = dom["config_path"].GetString();
        }
        if (dom.HasMember("tag_info") && dom["tag_info"].IsObject()) {
            const rapidjson::Value &object = dom["tag_info"].GetObject();
            if (object.HasMember("tag_name") && object["tag_name"].IsString()) {
                tag_.tag_name_ = object["tag_name"].GetString();
            }
        }
    }
}

void RequestTagList::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        SourceInfo::ToObj(data);
        if (dom.HasMember("page") && dom["page"].IsInt64()) {
            page_ = dom["page"].GetInt64();
        }
        if (dom.HasMember("size") && dom["size"].IsInt64()) {
            size_ = dom["size"].GetInt64();
        }
        if (dom.HasMember("kv") && dom["kv"].IsArray()) {
            auto d = dom["kv"].GetArray();
            for (int i = 0; i < d.Size(); i++) {
                Kv k;
                if (d[i].HasMember("key") && d[i]["key"].IsString()) {
                    k.key_ = d[i]["key"].GetString();
                }
                if (d[i].HasMember("value") && d[i]["value"].IsString()) {
                    k.value_ = d[i]["value"].GetString();
                }
                kvs_[k.key_] = k.value_;
            }
        }
    }
}

void RequestTagData::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        Tag::ToObj(data);
        TimeSection::ToObj(data);
    }
}

void RequestTagInfo::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        Tag::ToObj(data);
    }
}

void RequestGetHierarchical::ToObj(const std::string &data) {
    Kvs::ToObj(data);
}

void RequestGetEigenvalue::ToObj(const std::string &data) {
    Kvs::ToObj(data);
    range_.ToObj(data);
    tag_info_.ToObj(data);
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("order") && dom["order"].IsString()) {
            order_ = dom["order"].GetString();
        }
        if (dom.HasMember("verifies") && dom["verifies"].IsArray()) {
            auto tmp = dom["verifies"].GetArray();
            for (int i = 0; i < tmp.Size(); i++) {
                verifies_.emplace_back(tmp[i].GetString());
            }
        }
    }
}

void RequestDoTask::ToObj(const std::string &data) {
    Kvs::ToObj(data);
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("action") && dom["action"].IsString()) {
            action_ = dom["action"].GetString();
        }
        if (dom.HasMember("container_id") && dom["container_id"].IsString()) {
            container_id_ = dom["container_id"].GetString();
        }
        if (dom.HasMember("container_uid") && dom["container_uid"].IsString()) {
            container_uid_ = dom["container_uid"].GetString();
        }
        if (dom.HasMember("event_id") && dom["event_id"].IsString()) {
            event_id_ = dom["event_id"].GetString();
        }
        if (dom.HasMember("event_log_path") && dom["event_log_path"].IsString()) {
            event_log_path_ = dom["event_log_path"].GetString();
        }
        if (dom.HasMember("batch_id") && dom["batch_id"].IsString()) {
            batch_id_ = dom["batch_id"].GetString();
        }
        if (dom.HasMember("blocks") && dom["blocks"].IsArray()) {
            const rapidjson::Value &tmp = dom["blocks"];
            for (int i = 0; i < tmp.Size(); i++) {
                const rapidjson::Value &object = tmp[i];
                if (object.IsObject()) {
                    auto x = object.GetObject();
                    BlockMap b;
                    b.GetObj(x);
                    block_.push_back(b);
                }
            }
        }
    }
}

void RequestTagDataGet::ToObj(const std::string &data) {
    BlockInfo::ToObj(data);
    Kvs::ToObj(data);
}

void RequestGetNextBlockReq::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("tag_info") && dom["tag_info"].IsObject()) {
            auto tmp = dom["tag_info"].GetObject();
            tag_info_.GetObj(tmp);
        }

        if (dom.HasMember("kv") && dom["kv"].IsArray()) {
            auto d = dom["kv"].GetArray();
            for (int i = 0; i < d.Size(); i++) {
                Kv k;
                if (d[i].HasMember("key") && d[i]["key"].IsString()) {
                    k.key_ = d[i]["key"].GetString();
                }
                if (d[i].HasMember("value") && d[i]["value"].IsString()) {
                    k.value_ = d[i]["value"].GetString();
                }
                kvs_[k.key_] = k.value_;
            }
        }

        if (dom.HasMember("verifies") && dom["verifies"].IsArray()) {
            auto verifies = dom["verifies"].GetArray();
            for (int i = 0; i < verifies.Size(); i++) {
                verifies_.emplace_back(verifies[i].GetString());
            }
        }

        if (dom.HasMember("start") && dom["start"].IsInt64()) {
            start_ = dom["start"].GetInt64();
        }

        if (dom.HasMember("end") && dom["end"].IsInt64()) {
            end_ = dom["end"].GetInt64();
        }

        if (dom.HasMember("shard_size") && dom["shard_size"].IsInt64()) {
            shard_size_ = dom["shard_size"].GetInt64();
        }
    }
}

void RequestConfigSet::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("kv") && dom["kv"].IsArray()) {
            auto d = dom["kv"].GetArray();
            for (int i = 0; i < d.Size(); i++) {
                Kv k;
                if (d[i].HasMember("key") && d[i]["key"].IsString()) {
                    k.key_ = d[i]["key"].GetString();
                }
                if (d[i].HasMember("value") && d[i]["value"].IsString()) {
                    k.value_ = d[i]["value"].GetString();
                }
                kvs_[k.key_] = k.value_;
            }
        }
    }
}

void RequestGetEigenvalueByBlock::ToObj(const std::string &data) {
    Kvs::ToObj(data);
    block_info_.ToObj(data);
}
