#pragma once
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class CompressStatus
{
public:
	int status_ = 0;
public:
	void ToObj(std::string data);
	std::string ToString();

};
void CompressStatus::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("status") && doc["status"].IsInt()) {
			status_ = doc["status"].GetInt();
		}
	}
}
std::string CompressStatus::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("status");
	write.String(std::to_string(status_).c_str());
	write.EndObject();
	return strBuf.GetString();

}

