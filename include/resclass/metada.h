#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class Metadata
{
public:
	std::string tag_name_ = "";
	std::string field_name_ = "";
	int id_ =0;
	std::string tag_type_ = "";
	std::string	table_name_ = "";
	std::string database_ = "";
public:
	void ToObj(std::string data);
	std::string ToString();
	
};

void Metadata::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("tag_name") && doc["tag_name"].IsString()) {
			tag_name_ = doc["tag_name"].GetString();
		}
		if (doc.HasMember("field_name") && doc["field_name"].IsString()) {
			field_name_ = doc["field_name"].GetString();
		}
		if (doc.HasMember("id") && doc["id"].IsInt()) {
			id_ = doc["id"].GetInt();
		}
		if (doc.HasMember("tag_type") && doc["tag_type"].IsString()) {
			tag_type_ = doc["tag_type"].GetString();
		}
		if (doc.HasMember("table_name") && doc["table_name"].IsString()) {
			table_name_ = doc["table_name"].GetString();
		}
		if (doc.HasMember("database") && doc["database"].IsString()) {
			database_ = doc["database"].GetString();
		}
	}
}
std::string  Metadata::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("tag_name");
	write.String(tag_name_.c_str());
	write.Key("field_name");
	write.String(field_name_.c_str());
	write.Key("id");
	write.String(std::to_string(id_).c_str());
	write.Key("tag_type");
	write.String(tag_type_.c_str());
	write.Key("table_name");
	write.String(table_name_.c_str());
	write.Key("database");
	write.String(database_.c_str());
	write.EndObject();
	return strBuf.GetString();
	
}