//
// Created by ct on 2021/12/16.
//

#ifndef HIBEAT_META_H
#define HIBEAT_META_H

#include "string"
#include "map"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class Meta {
public:
    std::map<std::string, std::string> meta_;
public:
    void ToObj(const std::string &data);
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};


#endif //HIBEAT_META_H
