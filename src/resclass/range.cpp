//
// Created by ct on 2021/12/2.
//

#include <resclass/range.h>

void Range::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("range") && dom["range"].IsObject()) {
            auto tmp = dom["range"].GetObject();
            if (tmp.HasMember("start") && tmp["start"].IsInt64()) {
                start_ = tmp["start"].GetInt64();
            }
            if (tmp.HasMember("end") && tmp["end"].IsInt64()) {
                end_ = tmp["end"].GetInt64();
            }
        }
    }
}
