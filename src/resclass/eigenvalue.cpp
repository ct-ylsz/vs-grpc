//
// Created by ct on 2021/12/24.
//

#include "resclass/eigenvalue.h"

void Eigenvalue::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("value");
    write->String(value_.c_str());
    write->Key("per");
    write->Double(per_);
    write->Key("flag");
    write->Bool(flag_);
    write->EndObject();
}

void EigenvalueMap::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    for (auto &iter: eigenvalue_map_) {
        write->Key(iter.first.c_str());
        iter.second.ToJsonString(write);
    }
    write->EndObject();
}
