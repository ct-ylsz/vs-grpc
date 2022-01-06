//
// Created by ct on 2021/11/3.
//
#include "resclass/task.h"

void TaskPath::ToObj(const std::string& data) {
    rapidjson::Document doc;
    if (!doc.Parse(data.c_str()).HasParseError()) {
        if (doc.HasMember("read_path") && doc["read_path"].IsString()) {
            read_path_ = doc["read_path"].GetString();
        }
        if (doc.HasMember("write_path") && doc["write_path"].IsString()) {
            write_path_ = doc["write_path"].GetString();
        }
    }
}

void TaskPath::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc) {
    if (doc.HasMember("read_path") && doc["read_path"].IsString()) {
        read_path_ = doc["read_path"].GetString();
    }
    if (doc.HasMember("write_path") && doc["write_path"].IsString()) {
        write_path_ = doc["write_path"].GetString();
    }
}

std::string TaskPath::ToString() const {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("read_path");
    write.String(read_path_.c_str());
    write.Key("write_path");
    write.String(write_path_.c_str());
    write.EndObject();
    return strBuf.GetString();

}
