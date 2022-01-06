#pragma once

#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class Status {
public:
    int64_t start_ = 0;
    int64_t end_ = 0;
    int status_ = 0;
    std::string err_;
public:
    void ToObj(std::string data);

    std::string ToString();

};

void Status::ToObj(std::string data) {
    rapidjson::Document doc;
    if (!doc.Parse(data.c_str()).HasParseError()) {
        if (doc.HasMember("status") && doc["status"].IsInt()) {
            status_ = doc["status"].GetInt();
        }
    }
}

std::string Status::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("status");
    write.String(std::to_string(status_).c_str());
    write.Key("err");
    write.String(err_.c_str());
    write.Key("start");
    write.Int64(start_);
    write.Key("end");
    write.Int64(end_);
    write.EndObject();
    return strBuf.GetString();

}
