//
// Created by ct on 2021/12/18.
//

#include "resclass/nodeInfo.h"

std::string NodeInfo::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("container_id");
    write.String(container_id_.c_str());
    write.Key("container_name");
    write.String(container_name_.c_str());
    write.Key("action");
    write.String(action_.c_str());
    write.Key("ip");
    write.String(ip_.c_str());
    write.Key("port");
    write.Int(port_);
    write.Key("path_");
    write.String(action_.c_str());
    write.Key("status");
    write.Int(status_);
    write.Key("create_time");
    write.Int64(create_time_);
    write.Key("update_time");
    write.Int64(update_time_);
    write.EndObject();
    return strBuf.GetString();
}
