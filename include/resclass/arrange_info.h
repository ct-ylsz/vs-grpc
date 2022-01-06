//
// Created by ct on 2021/11/3.
//

#ifndef HIBEAT_ARRANGE_INFO_H
#define HIBEAT_ARRANGE_INFO_H
#include "sourceinfo.h"
#include "tag.h"
class ArrangeInfo : public SourceInfo,public Tag{
public:
    int arrange_type_ = 0;
public:
    int ToObj(const std::string& data);

    std::string ToString() const;
};
#endif //HIBEAT_ARRANGE_INFO_H
