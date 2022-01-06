//
// Created by ct on 2021/11/4.
//
#include "resclass/time_section.h"
void TimeSection::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer>* write)
{
    write->StartObject();
    write->Key("time_start");
    write->Int64(time_start_);
    write->Key("time_end");
    write->Int64(time_end_);
    write->EndObject();
}

std::string TimeSection::ToString() {
    rapidjson::StringBuffer str_buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
    write.StartObject();
    write.Key("time_start");
    write.Int64(time_start_);
    write.Key("time_end");
    write.Int64(time_end_);
    write.EndObject();
    return str_buf.GetString();
}

void TimeSection::ToObj(const std::string& data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("time_start") && dom["time_start"].IsInt64()) {
            time_start_ =  dom["time_start"].GetInt64();
        }
        if (dom.HasMember("time_end") && dom["time_end"].IsInt64()) {
            time_end_ =  dom["time_end"].GetInt64();
        }
    }
}
