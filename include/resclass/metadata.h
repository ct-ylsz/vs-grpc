//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_METADATA_H
#define HIBEAT_METADATA_H

#pragma once
#include <string>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "time_section.h"

class MetaData{
public:
    TimeSection time_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer>* write);
    std::string ToString();
    void ToObj(std::string data);
};

void MetaData::ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer>* write)
{
    time_.ToJsonString(write);
}

std::string MetaData::ToString() {
    return "";
}

void MetaData::ToObj(std::string data){

}

#endif //HIBEAT_METADATA_H
