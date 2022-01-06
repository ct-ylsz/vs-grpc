//
// Created by ct on 2021/12/1.
//

#include "resclass/hierarchy.h"

void Hierarchy::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("name");
    write->String(name_.c_str());
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
    if (!sublist_.empty()) {
        write->Key("sub_list");
        write->StartArray();
        for (auto v: sublist_) {
            v.ToJsonString(write);
        }
        write->EndArray();
    }
    write->EndObject();
}

void Hierarchies::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("list");
    write->StartArray();
    for (auto & i : list_) {
        i.ToJsonString(write);
    }
    write->EndArray();
    write->EndObject();
}
