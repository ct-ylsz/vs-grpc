#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class Container
{
public:
	std::string path_ = "";

public:
	void ToObj(std::string data);
	std::string ToString();
};
void Container::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {

		if (doc.HasMember("path") && doc["path"].IsString()) {
			path_ = doc["path"].GetString();
		}

	}
}
std::string  Container::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("path");
	write.String(path_.c_str());
	write.EndObject();
	return strBuf.GetString();

}
