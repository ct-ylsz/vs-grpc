//
// Created by ct on 2021/12/24.
//

#ifndef HIBEAT_IS_FREE_H
#define HIBEAT_IS_FREE_H

#include "iostream"
#include "string"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class IsFree {
public:
    int status_ = 0;
    int64_t mem_total_ = 0;
    int64_t mem_used_ = 0;
    int64_t cpu_total_ = 0;
    int64_t cpu_used_ = 0;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

#endif //HIBEAT_IS_FREE_H
