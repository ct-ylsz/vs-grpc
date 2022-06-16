//
// Created by ct on 2021/12/27.
//
#include "utils/util.h"
#include "ctime"
#include <Windows.h>

std::string RandStr(int length) {
    char tmp;
    std::string buffer;

    srand(time_t(NULL));
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

std::string UTF8_2_GBK(std::string utf8Str) {
    std::string outGBK = "";
    int n = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
    WCHAR *str1 = new WCHAR[n];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, n, NULL, NULL);
    outGBK = str2;
    delete[] str1;
    str1 = NULL;
    delete[] str2;
    str2 = NULL;
    return outGBK;
}