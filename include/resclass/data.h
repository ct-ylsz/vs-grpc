#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class Data
{
public:
	int num_ = 0;
	std::string ts_ = "";
public:
	void ToObj(std::string data);
	std::string ToString();

};
void Data::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("ts") && doc["ts"].IsString()) {
			ts_ = doc["ts"].GetString();
		}
		
		if (doc.HasMember("num") && doc["num"].IsInt()) {
			num_ = doc["num"].GetInt();
		}
		
	}
}
std::string  Data::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("ts");
	write.String(ts_.c_str());
	write.Key("num");
	write.String(std::to_string(num_).c_str());
	write.EndObject();
	return strBuf.GetString();

}

