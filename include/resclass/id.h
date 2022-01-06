#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class Id
{
public:
	int id_ = 0;
public:
	void ToObj(std::string data);
	std::string ToString();

};
void Id::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("id") && doc["id"].IsInt()) {
			id_ = doc["id"].GetInt();
		}
	}
}
std::string  Id::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("id");
	write.String(std::to_string(id_).c_str());
	write.EndObject();
	return strBuf.GetString();

}


