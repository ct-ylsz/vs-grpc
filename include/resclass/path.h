#pragma once

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class Path {
public:
    std::string config_path_ = "";
    std::string dll_path_ = "";
};

//class Path {
//public:
//    std::string read_path_ = "";
//    std::string write_path_ = "";
//public:
//    void ToObj(std::string data);
//
//    std::string ToString();
//
//};
//
//void Path::ToObj(std::string data) {
//    rapidjson::Document doc;
//    if (!doc.Parse(data.c_str()).HasParseError()) {
//
//        if (doc.HasMember("read_path") && doc["read_path"].IsString()) {
//            read_path_ = doc["read_path"].GetString();
//        }
//        if (doc.HasMember("write_path") && doc["write_path"].IsString()) {
//            write_path_ = doc["write_path"].GetString();
//        }
//    }
//}
//
//std::string Path::ToString() {
//    rapidjson::StringBuffer strBuf;
//    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
//    write.StartObject();
//    write.Key("read_path");
//    write.String(read_path_.c_str());
//    write.Key("write_path");
//    write.String(write_path_.c_str());
//    write.EndObject();
//    return strBuf.GetString();
//
//}
