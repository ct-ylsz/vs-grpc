//
// Created by ct on 2021/11/3.
//
#include "resclass/block.h"

void Block::ToObj(std::string data) {
    rapidjson::Document doc;
    if (!doc.Parse(data.c_str()).HasParseError()) {
        if (doc.HasMember("start") && doc["start"].IsInt64()) {
            start_ = doc["start"].GetInt64();
        }
        if (doc.HasMember("end") && doc["end"].IsInt64()) {
            end_ = doc["end"].GetInt64();
        }
        if (doc.HasMember("max") && doc["max"].IsInt()) {
            max_ = doc["max"].GetInt();
        }
        if (doc.HasMember("min") && doc["min"].IsInt()) {
            min_ = doc["min"].GetInt();
        }
        if (doc.HasMember("avg") && doc["avg"].IsInt()) {
            avg_ = doc["avg"].GetInt();
        }
        if (doc.HasMember("middle_num") && doc["middle_num"].IsInt()) {
            middle_num_ = doc["middle_num"].GetInt();
        }
    }
}

void Block::GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc) {
    if (doc.HasMember("start") && doc["start"].IsInt64()) {
        start_ = doc["start"].GetInt64();
    }
    if (doc.HasMember("end") && doc["end"].IsInt64()) {
        end_ = doc["end"].GetInt64();
    }
    if (doc.HasMember("max") && doc["max"].IsInt()) {
        max_ = doc["max"].GetInt();
    }
    if (doc.HasMember("min") && doc["min"].IsInt()) {
        min_ = doc["min"].GetInt();
    }
    if (doc.HasMember("avg") && doc["avg"].IsInt()) {
        avg_ = doc["avg"].GetInt();
    }
    if (doc.HasMember("middle_num") && doc["middle_num"].IsInt()) {
        middle_num_ = doc["middle_num"].GetInt();
    }
}

std::string Block::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("start");
    write.Int64(start_);
    write.Key("end");
    write.Int64(end_);
    write.Key("count");
    write.String(std::to_string(count_).c_str());
    write.Key("max");
    write.String(std::to_string(max_).c_str());
    write.Key("min");
    write.String(std::to_string(min_).c_str());
    write.Key("avg");
    write.String(std::to_string(avg_).c_str());
    write.Key("middle_num");
    write.String(std::to_string(middle_num_).c_str());
    write.EndObject();
    return strBuf.GetString();

}