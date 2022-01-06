//
// Created by ct on 2021/11/4.
//

#include "resclass/tag.h"

void Tag::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) const {
    write->StartObject();
    write->Key("name");
    write->String(tag_name_.c_str());
    write->Key("id");
    write->Int(tag_id_);
    write->Key("type");
    write->Int(type_);
    if (!meta_.empty()) {
        write->Key("meta");
        write->StartObject();
        for (const auto &v: meta_) {
            write->Key(v.first.c_str());
            write->String(v.second.c_str());
        }
        write->EndObject();
    }
    write->EndObject();
}

void Tag::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc) {
    if (doc.HasMember("tag_name") && doc["tag_name"].IsString()) {
        tag_name_ = doc["tag_name"].GetString();
    }
}

void Tag::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("tag_name") && dom["tag_name"].IsString()) {
            tag_name_ = dom["tag_name"].GetString();
        }
    }
}

void TagsInfo::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("list");
    write->StartArray();
    for (const auto &x: tags) {
        x.ToJsonString(write);
    }
    write->EndArray();
    write->EndObject();
}

std::string TagsInfo::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("data");
    write.StartArray();
    for (const auto &x: tags) {
        x.ToJsonString(&write);
    }
    write.EndArray();
    write.EndObject();
    return strBuf.GetString();
}

void TagInfoF::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("start");
    write->Int64(time_start_);
    write->Key("end");
    write->Int64(time_end_);
    write->Key("count");
    write->Int64(count_);
    write->Key("feature");
    write->StartObject();
    write->Key("min");
    write->Double(tag_desc_info_.min_);
    write->Key("max");
    write->Double(tag_desc_info_.max_);
    write->Key("avg");
    write->Double(tag_desc_info_.avg_);
    write->Key("sum");
    write->Double(tag_desc_info_.sum_);
    write->EndObject();
    write->EndObject();
}

void TagInfoDesc::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) const {
    write->StartObject();
    write->Key("min");
    write->Double(min_);
    write->Key("max");
    write->Double(max_);
    write->Key("desc");
    write->String(desc_.c_str());
    write->Key("unit");
    write->String(unit_.c_str());
    write->Key("name");
    write->String(name_.c_str());
    write->EndObject();
}

void TagInfoInternal::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("tag_info") && dom["tag_info"].IsObject()) {
            auto tmp = dom["tag_info"].GetObject();
            if (tmp.HasMember("tag_id") && tmp["tag_id"].IsString()) {
                tag_id_ = tmp["tag_id"].GetString();
            }
            if (tmp.HasMember("name") && tmp["name"].IsString()) {
                name_ = tmp["name"].GetString();
            }
            if (tmp.HasMember("type") && tmp["type"].IsInt()) {
                type_ = tmp["type"].GetInt();
            }
            if (tmp.HasMember("path") && tmp["path"].IsString()) {
                path_ = tmp["path"].GetString();
            }

            if (tmp.HasMember("extend_obj") && tmp["extend_obj"].IsObject()) {
                auto extend = tmp["extend_obj"].GetObject();
                for (rapidjson::Value::MemberIterator iter = extend.MemberBegin(); iter != extend.MemberEnd(); iter++) {
                    extend_obj_[iter->name.GetString()] = iter->value.GetString();
                }
            }

            if (tmp.HasMember("meta_") && tmp["meta_"].IsObject()) {
                auto extend = tmp["meta_"].GetObject();
                for (rapidjson::Value::MemberIterator iter = extend.MemberBegin(); iter != extend.MemberEnd(); iter++) {
                    meta_[iter->name.GetString()] = iter->value.GetString();
                }
            }
        }
    }
}

void
TagInfoInternal::GetObj(rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc) {
    if (doc.HasMember("name") && doc["name"].IsString()) {
        name_ = doc["name"].GetString();
    }
    if (doc.HasMember("tag_id") && doc["tag_id"].IsString()) {
        tag_id_ = doc["tag_id"].GetString();
    }
}
