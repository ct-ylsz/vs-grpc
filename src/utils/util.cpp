//
// Created by ct on 2021/12/27.
//
#include "utils/util.h"
#include "ctime"

std::string RandStr(int length) {
    char tmp;
    std::string buffer;

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        tmp = rand() % 36;
        if (tmp < 10) {
            tmp += '0';
        } else {
            tmp -= 10;
            tmp += 'A';
        }
        buffer += tmp;
    }
    return buffer;
}
