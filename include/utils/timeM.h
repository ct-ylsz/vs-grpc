#pragma once

#include <ctime>

class TimeM {
public:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;
    int hour_ = 0;
    int min_ = 0;
    int sec_ = 0;
public:
    void TimeStampToTime(time_t stamp);
};

void TimeM::TimeStampToTime(time_t stamp) {
#ifdef WIN32
    struct tm timeset{};
    gmtime_s(&timeset, &stamp);
    year_ = timeset.tm_year + 1900;
    month_ = timeset.tm_mon + 1;
    day_ = timeset.tm_mday;
    hour_ = timeset.tm_hour + 8;
    min_ = timeset.tm_min;
    sec_ = timeset.tm_sec;
    return;
#else
    struct tm* timeset2;
    timeset2 = gmtime(&stamp);
    year_ = timeset2->tm_year + 1900;
    month_ = timeset2->tm_mon + 1;
    day_ = timeset2->tm_mday;
    hour_ = timeset2->tm_hour + 8;
    min_ = timeset2->tm_min;
    sec_ = timeset2->tm_sec;
#endif
}