//
// Created by ct on 2021/12/16.
//

#include "resclass/meta.h"

void Meta::ToObj(const std::string &data) {
    rapidjson::Document dom;
    return;
}

void Meta::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    // write->StartObject();
    return;
//    for (auto iter = meta_.begin(); iter != meta_.end(); iter++) {
//        write->Key(iter->first.c_str());
//        write->String(iter->second.c_str());
//    }
//
//    write->Key("name");
//    write->String(name_.c_str());
//    write->Key("type");
//    write->Int(type_);
//    if (!meta_.empty()) {
//        write->Key("meta");
//        write->StartObject();
//        for (const auto &v: meta_) {
//            write->Key(v.first.c_str());
//            write->String(v.second.c_str());
//        }
//        write->EndObject();
//    }
//    if (!sublist_.empty()) {
//        write->Key("sub_list");
//        write->StartArray();
//        for (auto v: sublist_) {
//            v.ToJsonString(write);
//        }
//        write->EndArray();
//    }
//    write->EndObject();
}
