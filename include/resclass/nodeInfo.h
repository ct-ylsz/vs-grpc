//
// Created by ct on 2021/12/18.
//

#ifndef HIBEAT_NODEINFO_H
#define HIBEAT_NODEINFO_H

#include "string"
#include "map"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class NodeInfo {
public:
    std::string container_id_;
    std::string container_name_;
    std::string action_;
    std::string ip_;
    int port_;
    std::string path_;
    std::string docker_container_id_;
    int status_;
    int64_t create_time_;
    int64_t update_time_;
public:
    std::string ToString();
};

#endif //HIBEAT_NODEINFO_H
