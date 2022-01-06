#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class TaskWrite
{
public:
	int count_ = 0;
	int size_ = 0;
	std::string err_ = "";
public:
	void ToObj(std::string data);
	std::string ToString();

};
void TaskWrite::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("count") && doc["count"].IsInt()) {
			count_ = doc["count"].GetInt();
		}
		if (doc.HasMember("size") && doc["size"].IsInt()) {
			size_ = doc["size"].GetInt();
		}
		if (doc.HasMember("err") && doc["err"].IsString()) {
			err_ = doc["err"].GetString();
		}
	}
}
std::string  TaskWrite::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("count");
	write.String(std::to_string(count_).c_str());
	write.Key("size");
	write.String(std::to_string(size_).c_str());
	write.Key("err");
	write.String(err_.c_str());
	write.EndObject();
	return strBuf.GetString();

}
