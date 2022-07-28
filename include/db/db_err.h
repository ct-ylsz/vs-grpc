//
// Created by ct on 2021/11/9.
//

#ifndef PI_GRPC_DBERR_H
#define PI_GRPC_DBERR_H

#include <string>

enum kDbError {
    kDbOK = 0,
    kDbNetworkErr = -1,
    kDbConnectErr = -2,
    kDbSystemErr = -3,
    kDbUnknownErr = -4,
    kDbTagNotExist = -5,
    kDbValueNotExist = -6
};

class DbError {
public:
    kDbError err_code_ = kDbOK;
    std::string err_msg_ = "ok";

    [[nodiscard]] std::string ToString() const;
};

#endif //PI_GRPC_DBERR_H
