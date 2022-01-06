//
// Created by ct on 2021/11/2.
//
#include "resclass/sourceinfo.h"

void SourceInfo::ToObj(const std::string &data) {
    rapidjson::Document doc;
    if (doc.Parse(data.c_str()).HasParseError()) {
        return;
    }
    if (doc.HasMember("port") && doc["port"].IsInt()) {
        port_ = doc["port"].GetInt();
    }
    if (doc.HasMember("addr") && doc["addr"].IsString()) {
        addr_ = doc["addr"].GetString();
    }
    if (doc.HasMember("db_name") && doc["db_name"].IsString()) {
        db_name_ = doc["db_name"].GetString();
    }
    if (doc.HasMember("username") && doc["username"].IsString()) {
        username_ = doc["username"].GetString();
    }
    if (doc.HasMember("password") && doc["password"].IsString()) {
        password_ = doc["password"].GetString();
    }
    if (doc.HasMember("dll_path") && doc["dll_path"].IsString()) {
        dll_path_ = doc["dll_path"].GetString();
    }
    if (doc.HasMember("config_path") && doc["config_path"].IsString()) {
        config_path_ = doc["config_path"].GetString();
    }
}

void SourceInfo::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc) {
    if (doc.HasMember("port") && doc["port"].IsInt()) {
        port_ = doc["port"].GetInt();
    }
    if (doc.HasMember("addr") && doc["addr"].IsString()) {
        addr_ = doc["addr"].GetString();
    }
    if (doc.HasMember("db_name") && doc["db_name"].IsString()) {
        db_name_ = doc["db_name"].GetString();
    }
    if (doc.HasMember("username") && doc["username"].IsString()) {
        username_ = doc["username"].GetString();
    }
    if (doc.HasMember("password") && doc["password"].IsString()) {
        password_ = doc["password"].GetString();
    }
    if (doc.HasMember("dll_path") && doc["dll_path"].IsString()) {
        dll_path_ = doc["dll_path"].GetString();
    }
    if (doc.HasMember("config_path") && doc["config_path"].IsString()) {
        config_path_ = doc["config_path"].GetString();
    }
}

std::string SourceInfo::ToString() const {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("addr");
    write.String(addr_.c_str());
    write.Key("db_name");
    write.String(db_name_.c_str());
    write.Key("username");
    write.String(username_.c_str());
    write.Key("password");
    write.String(password_.c_str());
    write.Key("port");
    write.Int(port_);
    write.EndObject();
    return strBuf.GetString();
}