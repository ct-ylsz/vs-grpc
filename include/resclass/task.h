#pragma once
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class TaskPath
{
public:
	std::string read_path_ = "";
    std::string write_path_ = "";
public:
	void ToObj(const std::string& data);
    void GetObj(rapidjson::GenericObject<true, rapidjson::GenericValue<rapidjson::UTF8<>>::ValueType> &);
	std::string ToString() const;
};

