//
// Created by ct on 2021/11/30.
//

#ifndef HIBEAT_KV_H
#define HIBEAT_KV_H

#include <string>
#include <vector>
#include <map>
class Kv {
public:
    std::string key_;
    std::string value_;
};

class Kvs {
public:
    std::map<std::string, std::string> kvs_;
public:
    void ToObj(const std::string &data) {
        rapidjson::Document dom;
        if (!dom.Parse(data.c_str()).HasParseError()) {
            if (dom.HasMember("kv") && dom["kv"].IsArray()) {
                auto d = dom["kv"].GetArray();
                for (int i = 0; i < d.Size(); i++) {
                    Kv k;
                    if (d[i].HasMember("key") && d[i]["key"].IsString()) {
                        k.key_ = d[i]["key"].GetString();
                    }
                    if (d[i].HasMember("value") && d[i]["value"].IsString()) {
                        k.value_ = d[i]["value"].GetString();
                    }
                    kvs_[k.key_] = k.value_;
                }
            }
        }
    }
};

#endif //HIBEAT_KV_H
