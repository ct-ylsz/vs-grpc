#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
class THLCotainerWrite
{
public:
	int id_ = 0;
	std::string container_id_ = "";
	std::string container_type_ = "";
	std::string ip_ = "";
	std::string port_ = "";
	int cpu_ = 0;
	int mem_ = 0;
	int disk_ = 0;
	int net_io_ = 0;
	std::string update_time_ = "";
	std::string create_time_ = "";
	int status_ = 0;
public:
	void ToObj(std::string data);
	std::string ToString();

};
void THLCotainerWrite::ToObj(std::string data) {
	rapidjson::Document doc;
	if (!doc.Parse(data.c_str()).HasParseError()) {

		if (doc.HasMember("id") && doc["id"].IsInt()) {
			id_ = doc["id"].GetInt();
		}

		if (doc.HasMember("cpu") && doc["cpu"].IsInt()) {
			cpu_ = doc["cpu"].GetInt();
		}

		if (doc.HasMember("mem") && doc["men"].IsInt()) {
			mem_ = doc["men"].GetInt();
		}

		if (doc.HasMember("disk") && doc["disk"].IsInt()) {
			disk_ = doc["disk"].GetInt();
		}

		if (doc.HasMember("net_io") && doc["net_io"].IsInt()) {
			net_io_ = doc["net_io"].GetInt();
		}
		if (doc.HasMember("container_id") && doc["container_id"].IsString()) {
			container_id_ = doc["container_id"].GetString();
		}
		if (doc.HasMember("container_type") && doc["container_type"].IsString()) {
			container_type_ = doc["container_type"].GetString();
		}
		if (doc.HasMember("ip") && doc["ip"].IsString()) {
			ip_ = doc["ip"].GetString();
		}
		if (doc.HasMember("port") && doc["port"].IsString()) {
			port_ = doc["port"].GetString();
		}
		if (doc.HasMember("update_time") && doc["update_time"].IsString()) {
			update_time_ = doc["update_time"].GetString();
		}
		if (doc.HasMember("create_time") && doc["create_time"].IsString()) {
			create_time_ = doc["create_time"].GetString();
		}
		if (doc.HasMember("status") && doc["status"].IsInt()) {
			status_ = doc["status"].GetInt();
		}
	}
}
std::string  THLCotainerWrite::ToString() {
	rapidjson::StringBuffer strBuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
	write.StartObject();
	write.Key("id");
	write.String(std::to_string(id_).c_str());
	write.Key("cpu");
	write.String(std::to_string(cpu_).c_str());
	write.Key("mem");
	write.String(std::to_string(mem_).c_str());
	write.Key("disk");
	write.String(std::to_string(disk_).c_str());
	write.Key("net_io");
	write.String(std::to_string(net_io_).c_str());
	write.Key("container_id");
	write.String(container_id_.c_str());
	write.Key("container_type");
	write.String(container_type_.c_str());
	write.Key("ip");
	write.String(ip_.c_str());
	write.Key("port");
	write.String(port_.c_str());
	write.Key("update_time");
	write.String(update_time_.c_str());
	write.Key("create_time");
	write.String(create_time_.c_str());
	write.Key("status");
	write.String(std::to_string(status_).c_str());
	write.EndObject();
	return strBuf.GetString();

}

