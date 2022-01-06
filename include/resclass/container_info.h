//
// Created by ct on 2021/11/2.
//

#ifndef HIBEAT_CONTAINER_INFO_H
#define HIBEAT_CONTAINER_INFO_H

#include  <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class ContainerInfo {
public:
    std::string container_id_ = "";        //容器id
    std::string container_type_ = "";    //容器类型
    std::string ip_ = "";                            //监听的ip
    std::string port_ = "";                        //监听的端口
    std::string cpu_ = "";                        //CPU使用率
    std::string mem_ = "";                    //内存剩余
    std::string disk_ = "";                        //文件仓库挂载的硬盘使用率
    std::string net_io_ = "";                    //网络io
    std::string update_time_ = "";        //更新时间
    std::string create_time_ = "";        //创建时间
    int status_ = 0;                                //程序状态

public:
    std::string ToString();
};

std::string ContainerInfo::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("id");
    write.String(container_id_.c_str());
    write.Key("container_type");
    write.String(container_type_.c_str());
    write.Key("ip");
    write.String(ip_.c_str());
    write.Key("port");
    write.String(port_.c_str());
    write.Key("cpu");
    write.String(cpu_.c_str());
    write.Key("mem");
    write.String(mem_.c_str());
    write.Key("disk");
    write.String(disk_.c_str());
    write.Key("net_io");
    write.String(net_io_.c_str());
    write.Key("create_time");
    write.String(create_time_.c_str());
    write.Key("status");
    write.Int(status_);
    write.EndObject();
    return strBuf.GetString();
}

#endif //HIBEAT_CONTAINER_INFO_H
