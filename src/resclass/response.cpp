//
// Created by ct on 2021/11/2.
//

#include "resclass/response.h"

/*
std::string ResponseHttp::ToString()
{
    rapidjson::StringBuffer str_buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
    write.StartObject();
    write.Key("code");
    write.Int(code_);
    write.Key("msg");
    write.String(msg_.c_str());
    write.EndObject();
    return str_buf.GetString();
}
*/

/*
template <class T>
std::string ResponseHttp::ToString(T rel_type)
{
    rapidjson::StringBuffer str_buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
    write.StartObject();
    write.Key("code");
    write.Int(code_);
    write.Key("msg");
    write.String(msg_.c_str());
    write.Key("timestamp");
    write.Int64(0);
    write.Key("data");
    rel_type.ToJsonString(&write);
    write.EndObject();
    return str_buf.GetString();
}
*/
