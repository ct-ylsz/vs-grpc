//
// Created by ct on 2021/12/1.
//

#ifndef HIBEAT_HIERARCHY_H
#define HIBEAT_HIERARCHY_H

#include <map>
#include <vector>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

//Hierarchy ²ã¼¶¹ØÏµ
class Hierarchy {
public:
    std::string name_;
    int type_;
    std::map<std::string, std::string> meta_;
    std::vector<Hierarchy> sublist_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

class Hierarchies{
public:
    std::vector<Hierarchy> list_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

#endif //HIBEAT_HIERARCHY_H
