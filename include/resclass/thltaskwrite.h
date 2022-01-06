#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class TLHTaskWrite
{
public:
	int start_ = 0;
	int end_ = 0;
	int count_ = 0;
	std::string err_ = "";
public:
	void ToObj(std::string data);
	std::string ToString();

};
void TLHTaskWrite::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("start") && doc["start"].IsInt()) {
			start_ = doc["start"].GetInt();
		}
		if (doc.HasMember("end") && doc["end"].IsInt()) {
			end_ = doc["end"].GetInt();
		}
		if (doc.HasMember("count") && doc["count"].IsInt()) {
			count_ = doc["count"].GetInt();
		}

		if (doc.HasMember("err") && doc["err"].IsString()) {
			err_ = doc["err"].GetString();
		}
	}
}
std::string  TLHTaskWrite::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("start");
	write.String(std::to_string(start_).c_str());
	write.Key("end");
	write.String(std::to_string(end_).c_str());
	write.Key("count");
	write.String(std::to_string(count_).c_str());
	write.Key("err");
	write.String(err_.c_str());
	write.EndObject();
	return strBuf.GetString();

}

