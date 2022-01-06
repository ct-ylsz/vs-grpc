//
// Created by ct on 2021/11/5.
//

#include "resclass/tag_data.h"

void TagDataF::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartArray();
    for (auto x: tags_) {
        x.ToJsonString(write);
    }
    write->EndArray();
}

void TagDataInfo::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("ts");
    write->Int64(ts_);
    write->Key("value");
    write->Double(value_);
    write->Key("status");
    write->Int(status_);
    write->EndObject();
}
