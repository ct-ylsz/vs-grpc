//
// Created by ct on 2021/12/2.
//

#include "resclass/blockInfo.h"

void BlockInfo::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    SimpleBlockInfo::ToJsonString(write);
    write->Key("path");
    write->String(path_.c_str());
    if (!extend_obj_.empty()) {
        write->Key("extend_obj");
        write->StartObject();
        for (const auto &v: extend_obj_) {
            write->Key(v.first.c_str());
            write->String(v.second.c_str());
        }
        write->EndObject();
    }
    write->EndObject();
}

void BlockInfo::ToObj(const std::string &data) {
    SimpleBlockInfo::ToObj(data);
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("block_info") && dom["block_info"].IsObject()) {
            auto tmp = dom["block_info"].GetObject();
            if (tmp.HasMember("extend_obj") && tmp["extend_obj"].IsObject()) {
                auto extend = tmp["extend_obj"].GetObject();
                for (rapidjson::Value::MemberIterator iter = extend.MemberBegin(); iter != extend.MemberEnd(); iter++) {
                    if (iter->value.IsString()) {
                        extend_obj_[iter->name.GetString()] = extend_obj_[iter->value.GetString()];
                    }
                }
            }
            if (tmp.HasMember("path") && tmp["path"].IsString()) {
                path_ = tmp["path"].GetString();
            }
        }
    }
}

void BlockInfo::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &tmp) {
    if (tmp.HasMember("extend_obj") && tmp["extend_obj"].IsObject()) {
        auto extend = tmp["extend_obj"].GetObject();
        for (rapidjson::Value::ConstMemberIterator iter = extend.MemberBegin(); iter != extend.MemberEnd(); iter++) {
            std::string value;
            if (iter->value.IsInt64()) {
                value = std::to_string(iter->value.GetInt64());
            } else {
                value = iter->value.GetString();
            }
            extend_obj_[iter->name.GetString()] = value;
        }
    }
    if (tmp.HasMember("path") && tmp["path"].IsString()) {
        path_ = tmp["path"].GetString();
    }
    if (tmp.HasMember("block_id") && tmp["block_id"].IsString()) {
        block_id_ = tmp["block_id"].GetString();
    }
    if (tmp.HasMember("start") && tmp["start"].IsInt64()) {
        start_ = tmp["start"].GetInt64();
    }
    if (tmp.HasMember("end") && tmp["end"].IsInt64()) {
        end_ = tmp["end"].GetInt64();
    }
    if (tmp.HasMember("count") && tmp["count"].IsInt64()) {
        count_ = tmp["count"].GetInt64();
    }
    if (tmp.HasMember("eigenvalue") && tmp["eigenvalue"].IsObject()) {
        auto e = tmp["eigenvalue"].GetObject();

    }
}

void SimpleBlockInfo::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->Key("block_id");
    write->String(block_id_.c_str());
    write->Key("start");
    write->Int64(start_);
    write->Key("end");
    write->Int64(end_);
    write->Key("count");
    write->Int64(count_);
    write->Key("eigenvalue");
    write->StartObject();
    for (const auto &v: eigenvalue_map_) {
        write->Key(v.first.c_str());
        write->StartObject();
        write->Key("value");
        write->String(v.second.value_.c_str());

        write->Key("flag");
        write->Bool(v.second.flag_);

        write->Key("per");
        write->Double(v.second.per_);

        write->EndObject();
    }
    write->EndObject();
}

void SimpleBlockInfo::ToObj(std::string data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("block_info") && dom["block_info"].IsObject()) {
            auto tmp = dom["block_info"].GetObject();
            if (tmp.HasMember("block_id") && tmp["block_id"].IsString()) {
                block_id_ = tmp["block_id"].GetString();
            }
            if (tmp.HasMember("start") && tmp["start"].IsInt64()) {
                start_ = tmp["start"].GetInt64();
            }
            if (tmp.HasMember("end") && tmp["end"].IsInt64()) {
                end_ = tmp["end"].GetInt64();
            }
            if (tmp.HasMember("count") && tmp["count"].IsInt64()) {
                count_ = tmp["count"].GetInt64();
            }
        }
    }
}

void
SimpleBlockInfo::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &tmp) {
    if (tmp.HasMember("block_id") && tmp["block_id"].IsString()) {
        block_id_ = tmp["block_id"].GetString();
    }
    if (tmp.HasMember("start") && tmp["start"].IsInt64()) {
        start_ = tmp["start"].GetInt64();
    }
    if (tmp.HasMember("end") && tmp["end"].IsInt64()) {
        end_ = tmp["end"].GetInt64();
    }
    if (tmp.HasMember("count") && tmp["count"].IsInt64()) {
        count_ = tmp["count"].GetInt64();
    }
}

void BlockMap::ToObj(std::string data) {
    BlockInfo::ToObj(data);
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("schedule_file") && dom["schedule_file"].IsString()) {
            block_["schedule_file"] = dom["schedule_file"].GetString();
        }
        if (dom.HasMember("source_file") && dom["source_file"].IsString()) {
            block_["source_file"] = dom["source_file"].GetString();
        }
        if (dom.HasMember("target_file") && dom["target_file"].IsString()) {
            block_["target_file"] = dom["target_file"].GetString();
        }
    }
}

void BlockMap::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &dom) {
    if (dom.HasMember("schedule_file") && dom["schedule_file"].IsString()) {
        block_["schedule_file"] = dom["schedule_file"].GetString();
    }
    if (dom.HasMember("source_file") && dom["source_file"].IsString()) {
        block_["source_file"] = dom["source_file"].GetString();
    }
    if (dom.HasMember("target_file") && dom["target_file"].IsString()) {
        block_["target_file"] = dom["target_file"].GetString();
    }
    if (dom.HasMember("block_info") && dom["block_info"].IsObject()) {
        auto tmp = dom["block_info"].GetObject();
        BlockInfo::GetObj(tmp);
    }
}
