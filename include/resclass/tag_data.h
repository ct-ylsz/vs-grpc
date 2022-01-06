//
// Created by ct on 2021/11/5.
//

#ifndef HIBEAT_TAGDATA_H
#define HIBEAT_TAGDATA_H
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class TagDataInfo{
public:
    long ts_ = 0;
    double value_ = 0.0;
    int status_ = 0;

public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

class TagDataF {
public:
    std::vector<TagDataInfo> tags_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};

#endif //HIBEAT_TAGDATA_H
