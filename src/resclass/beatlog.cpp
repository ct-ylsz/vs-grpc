//
// Created by ct on 2021/12/16.
//

#include "resclass/beatlog.h"

std::string BeatLog::ToString() {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("start_time");
    write.Int64(start_time_);
    write.Key("end_time");
    write.Int64(end_time_);
    write.Key("tag_id");
    write.String(tag_id_.c_str());
    write.Key("batch_id");
    write.String(batch_id_.c_str());
    write.Key("container_id");
    write.String(container_id_.c_str());
    write.Key("container_uid");
    write.String(container_uid_.c_str());
    write.Key("block_id");
    write.String(block_id_.c_str());
    write.Key("event_id");
    write.String(event_id_.c_str());
    write.Key("msg");
    write.String(msg_.c_str());
    write.Key("status");
    write.Int(status_);
    write.EndObject();
    return strBuf.GetString();
}
