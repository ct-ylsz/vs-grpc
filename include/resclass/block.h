
#pragma once

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include<iostream>

class Block {
public:
    long start_ = 0;
    long end_ = 0;
    int count_ = 0;
    int max_ = 0;
    int min_ = 0;
    int avg_ = 0;
    int middle_num_ = 0;
public:
    void ToObj(std::string data);

    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);

    std::string ToString();

};

