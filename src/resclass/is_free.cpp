//
// Created by ct on 2021/12/24.
//

#include "resclass/is_free.h"

void IsFree::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) {
    write->StartObject();
    write->Key("mem_total");
    write->Int64(mem_total_);
    write->Key("mem_used");
    write->Int64(mem_used_);
    write->Key("cpu_total");
    write->Int64(cpu_total_);
    write->Key("cpu_used");
    write->Int64(cpu_used_);
    write->Key("status");
    write->Int64(status_);
    write->EndObject();
}
