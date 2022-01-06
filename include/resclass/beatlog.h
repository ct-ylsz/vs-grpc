//
// Created by ct on 2021/12/16.
//

#ifndef HIBEAT_BEATLOG_H
#define HIBEAT_BEATLOG_H

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include<iostream>

class BeatLog {
public:
    std::string event_id_;
    std::string batch_id_;
    std::string container_id_;
    std::string container_uid_;
    std::string tag_id_;
    std::string block_id_;
    int64_t start_time_;
    int64_t end_time_;
    std::string msg_;
    int status_;
public:
    std::string ToString();
};

#endif //HIBEAT_BEATLOG_H
