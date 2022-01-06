//
// Created by ct on 2021/12/1.
//

#ifndef HIBEAT_EIGENVALUE_H
#define HIBEAT_EIGENVALUE_H

#include <string>
#include <map>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class Eigenvalue {
public:
    std::string value_;
    bool flag_;
    float per_ = 0.0;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

class EigenvalueMap {
public:
    std::map<std::string, Eigenvalue> eigenvalue_map_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};


#endif //HIBEAT_EIGENVALUE_H
