#pragma once
#include<string>
#include<vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class TaskInfo
{
public:
	std::string source_path_ = "";
	std::string arrange_path_ = "";
	std::vector<std::string>block_paths_;
	std::string source_type_ = "";
	std::string start_time_ = "";
	std::string end_time_ = "";
	std::string out_type_ = "";
public:
	void ToObj(std::string data);
	std::string ToString();
};
void TaskInfo::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {
		if (doc.HasMember("source_path") && doc["source_path"].IsString()) {
			source_path_ = doc["source_path"].GetString();
		}
		if (doc.HasMember("arrange_path") && doc["arrange_path"].IsString()) {
			arrange_path_ = doc["arrange_path"].GetString();
		}
		if (doc.HasMember("block_paths") && doc["block_paths"].IsArray()) {
			auto curent_block_paths_ = doc["block_paths"].GetArray();
			for (int i = 0; i < curent_block_paths_.Size(); i++)
			{
				block_paths_[i] = curent_block_paths_[i].GetString();
			}
		}
		if (doc.HasMember("source_type") && doc["source_type"].IsString()) {
			source_type_ = doc["source_type"].GetString();
		}
		if (doc.HasMember("start_time") && doc["start_time"].IsString()) {
			start_time_ = doc["start_time"].GetString();
		}
		if (doc.HasMember("end_time") && doc["end_time"].IsString()) {
			end_time_ = doc["end_time"].GetString();
		}
		if (doc.HasMember("out_type") && doc["out_type"].IsString()) {
			out_type_ = doc["out_type"].GetString();
		}
	}
}
std::string  TaskInfo::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("source_path");
	write.String(source_path_.c_str());
	write.Key("arrange_path");
	write.String(arrange_path_.c_str());
	write.Key("block_paths");
	write.StartArray();
	for (int i = 0; i < block_paths_.size(); i++)
	{
		write.String(block_paths_[i].c_str());
	}
	write.EndArray();
	write.Key("source_type");
	write.String(source_type_.c_str());
	write.Key("start_time");
	write.String(start_time_.c_str());
	write.Key("end_time");
	write.String(end_time_.c_str());
	write.Key("out_type");
	write.String(out_type_.c_str());
	write.EndObject();
	return strBuf.GetString();

}

