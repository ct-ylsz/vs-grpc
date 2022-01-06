//
// Created by ct on 2021/11/2.
//

#ifndef HIBEAT_TAG_H
#define HIBEAT_TAG_H

#include <string>
#include <vector>
#include <iostream>
#include <vs/RTDBDefine.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "time_section.h"
#include <map>

class Tag {
public:
    std::string tag_name_;
    int tag_id_ = 0;
    int type_ = 3;
    std::map<std::string, std::string> meta_;
public:
    void ToObj(const std::string &data);

    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) const;

    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc);
};


class TagsInfo {
public:
    std::vector<Tag> tags;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);

    std::string ToString();
};


class TagDescInfo {
public:
    double max_ = 0.0;//最大值 编排规则中每个select字段的max平均值
    double min_ = 0.0;     //最小值 编排规则中每个select字段的min平均值
    double avg_ = 0.0;     //平均数 编排规则中每个select字段的avg平均值
    double middle_num_ = 0.0; //中位数 编排规则中每个select字段的中位数平均值
    double sum_ = 0.0;     //总和数
    double null_num_ = 0.0; //空值数量
    double repeated_num_ = 0.0;//重复数
    double size_ = 0.0;     //文件大小
};

class TagInfoF : public TimeSection {
public:
    TagDescInfo tag_desc_info_{};
    int count_ = 0;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write);
};


class TagInfoDesc {
public:
    std::string name_;
    std::string desc_;
    double max_;
    double min_;
    std::string unit_;
public:
    void ToJsonString(rapidjson::PrettyWriter<rapidjson::StringBuffer> *write) const;
};

class TagValue {
public:
    int32_t ts;
    float value;
};


class TagInfoInternal {
public:
    std::string tag_id_;
    std::string name_;
    int type_;
    std::map<std::string, std::string> meta_;
    std::map<std::string, std::string> extend_obj_;
    std::string path_;

public:
    void ToObj(const std::string &data);
    void GetObj(rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &doc);
};

#endif //HIBEAT_TAG_H
