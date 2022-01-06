//
// Created by ct on 2021/11/3.
//
#include "resclass/arrange_info.h"

int ArrangeInfo::ToObj(const std::string &data) {
    rapidjson::Document dom;
    if (!dom.Parse(data.c_str()).HasParseError()) {
        if (dom.HasMember("arrange_type") && dom["arrange_type"].IsInt()) {
            arrange_type_ = dom["arrange_type"].GetInt();
        }
    }
    return 0;
}