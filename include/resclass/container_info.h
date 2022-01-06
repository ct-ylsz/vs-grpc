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
    std::string container_id_ = "";        //����id
    std::string container_type_ = "";    //��������
    std::string ip_ = "";                            //������ip
    std::string port_ = "";                        //�����Ķ˿�
    std::string cpu_ = "";                        //CPUʹ����
    std::string mem_ = "";                    //�ڴ�ʣ��
    std::string disk_ = "";                        //�ļ��ֿ���ص�Ӳ��ʹ����
    std::string net_io_ = "";                    //����io
    std::string update_time_ = "";        //����ʱ��
    std::string create_time_ = "";        //����ʱ��
    int status_ = 0;                                //����״̬

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
