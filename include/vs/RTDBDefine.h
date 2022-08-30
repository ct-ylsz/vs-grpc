#pragma once

#ifndef _RTDB_DEFINE_H__
#define _RTDB_DEFINE_H__


#define RTDB_TAGNAME_LENGTH 128        //测点点名最大长度
#define RTDB_TAGDESC_LENGTH 128        //测点描述最大长度
#define RTDB_TAGUNIT_LENGTH 16        //测点单位最大长度

#define RTDB_MAX_DATACOUNT  1024    //最大数据个数

#define RTDB_DATATYPE_RAW 0            //测点数据类型，原始值
#define RTDB_DATATYPE_MAX 1            //测点数据类型，最大值
#define RTDB_DATATYPE_MIN 2            //测点数据类型，最小值
#define RTDB_DATATYPE_AVG 3            //测点数据类型，平均值
#define RTDB_DATATYPE_SNP 4            //测点数据类型，快照值

#define RTDB_DATASTATUS_GOOD 0            //测点数据状态，质量好
#define RTDB_DATASTATUS_BAD 1            //测点数据状态，质量坏
#define RTDB_DATASTATUS_MANUAL 2        //测点数据状态，人工置入
#define RTDB_DATASTATUS_TAGNOTEXIST 3    //测点数据状态，点名不存在
#define RTDB_DATASTATUS_WRITESUCCESS 4    //测点数据状态，写入成功
#define RTDB_DATASTATUS_DATANOTEXIST 5    //测点数据状态，数据不存在
#define RTDB_DATASTATUS_WRITEFAILED  6  //测点数据状态，数据写入失败

#define RTDB_RETURNSTATUS_SUCCESS   0        //查询成功
#define RTDB_RETURNSTATUS_NETECP    -1       //网络异常
#define RTDB_RETURNSTATUS_DATABASEECP -2     //数据库异常
#define RTDB_RETURNSTATUS_SYSECP    -3       //系统异常
#define RTDB_RETURNSTATUS_OTHERECP   -4         //其他异常
#define RTDB_RETURNSTATUS_POINTNOEXIST   -5  //测点不存在
#define RTDB_RETURNSTATUS_DATANOEXIST    -6  //数据不存在
#define RTDB_RETURNSTATUS_DBFUNCECP     -7   //数据库函数执行失败
#define RTDB_RETURNSTATUS_DBFUNCTO      -8   //数据库函数执行超时

#define RTDB_TAGTYPE_A 1        //测点类型，模拟量
#define RTDB_TAGTYPE_D 0        //测点类型，开关量


//***************************************
//测点数据结构体
//***************************************
typedef struct TagData_struct {
    double value;        //返回点的数值
    long time;        //返回点的时间，秒
    int status;        //返回点的状态
} TagData;


//**************************************
//查询历史记录请求包的结构
//**************************************
typedef struct ReadHiDataRequest_struct {
    long stTime;                //查询点记录的开始时间，秒
    long enTime;                //查询点记录的结束时间，秒
    long tPeriod;                //查询点值的时间间隔，秒
    int reqType;                //查询的数据类型（原始=0，最大=1，最小=2，平均=3,快照=4）
    char pointName[RTDB_TAGNAME_LENGTH];        //请求的完整点名
} ReadHiDataRequest;


//************************************
//测点信息结构体
//************************************
typedef struct TagInfo_struct {
    double max;
    double min;
    char unit[RTDB_TAGUNIT_LENGTH];
    char desc[RTDB_TAGDESC_LENGTH];
    char name[RTDB_TAGNAME_LENGTH];
} TagInfo;

//************************************
//给已有记录点插入数据结构体
//************************************
typedef struct InsertData_struct {
    int type;            //为0则为开关量，为1则为摸拟量
    int status;        //写入点记录的状态
    double value;        //写入点记录的值
    long time;            //写入点记录的时间，秒
    char pointName[RTDB_TAGNAME_LENGTH];    //写入点的完整点名
} InsertData;


#endif