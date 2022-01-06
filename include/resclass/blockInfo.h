//
// Created by ct on 2021/12/1.
//

#ifndef HIBEAT_BLOCKINFO_H
#define HIBEAT_BLOCKINFO_H

#include "eigenvalue.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "path.h"

class SimpleBlockInfo : public EigenvalueMap {
public:
    std::string block_id_;
    int64_t start_;
    int64_t end_;
    int64_t count_ = 0;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);

    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);

    void ToObj(std::string data);
};

class BlockInfo : public SimpleBlockInfo {
public:
    std::map<std::string, std::string> extend_obj_;
    std::string path_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);

    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);

    void ToObj(const std::string &data);
};

class BlockMap : public BlockInfo, public Path {
public:
    std::map<std::string, std::string> block_;
public:
    void ToObj(std::string data);

    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);

};


#endif //HIBEAT_BLOCKINFO_H
