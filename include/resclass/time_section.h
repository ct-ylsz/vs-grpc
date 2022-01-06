//
// Created by ct on 2021/11/2.
//

#ifndef HIBEAT_TIME_SECTION_H
#define HIBEAT_TIME_SECTION_H

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class TimeSection {
public:
    int64_t time_start_ = 0;
    int64_t time_end_ = 0;
public:
    void ToObj(const std::string &data);

    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);

    std::string ToString();
};


#endif //HIBEAT_TIME_SECTION_H
