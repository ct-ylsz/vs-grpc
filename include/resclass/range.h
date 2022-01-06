//
// Created by ct on 2021/12/2.
//

#ifndef HIBEAT_RANGE_H
#define HIBEAT_RANGE_H

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class Range {
public:
    int64_t start_ = 0;
    int64_t end_ = 0;
public:
    void ToObj(const std::string &data);
};


#endif //HIBEAT_RANGE_H
