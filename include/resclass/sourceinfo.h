//
// Created by ct on 2021/11/2.
//

#ifndef HIBEAT_SOURCEINFO_H
#define HIBEAT_SOURCEINFO_H

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class SourceInfo {
public:
    std::string addr_;
    std::string db_name_;
    std::string username_;
    std::string password_;
    int port_ = 0;
    std::string dll_path_ = "";
    std::string config_path_ = "";
public:
    void ToObj(const std::string& data);
    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);
    std::string ToString() const;
};




#endif //HIBEAT_SOURCEINFO_H
