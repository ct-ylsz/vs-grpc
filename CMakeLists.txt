cmake_minimum_required(VERSION 3.20)

project(vs-grpc)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
# 头文件
set(THIRD_PARTY_DIR ./thirdparty)
set(GRPC_INCLUDE D:\\grpclib\\grpc32\\grpc\\include)
set(PROTO_INCLUDE ./proto)
set(INCLUDE ./include)
set(BOOST_INCLUDE D:\\boost_1_70_0)
set(YAML_INCLUDE D:\\yaml\\YAML_CPP\\include)
include_directories(${GRPC_INCLUDE} ${PROTO_INCLUDE} ${THIRD_PARTY_DIR} ${BOOST_INCLUDE} ${INCLUDE} ${YAML_INCLUDE})

# 库文件
set(GRPC_LIB D:\\grpclib\\grpc32\\grpc\\lib)
set(LIB ./lib)
set(BOOST_LIB D:\\boost_1_70_0\\stage\\lib)
set(YAML_LIB D:\\yaml\\YAML_CPP\\lib)
link_directories(${GRPC_LIB} ${LIB} ${BOOST_LIB} ${YAML_LIB})


add_executable(vs-grpc main.cpp proto/vs.grpc.pb.cc proto/vs.pb.cc src/utils/file.cpp src/db/dberr.cpp src/service/service.hpp src/db/db.cpp src/resclass/tag.cpp src/utils/config.cpp src/utils/util.cpp)
target_link_libraries(vs-grpc libprotobufd.lib grpc grpc++
        gpr
        zlibd
        cares
        address_sorting
        upb
        absl_str_format_internal
        absl_strings
        absl_strings_internal
        absl_cord
        absl_bad_optional_access
        absl_base
        absl_throw_delegate
        absl_time
        absl_time_zone
        absl_int128
        absl_raw_logging_internal
        crypto
        ssl
        re2
        absl_status
        absl_statusor
        absl_synchronization
        absl_malloc_internal
        absl_graphcycles_internal
        absl_stacktrace
        absl_symbolize
        absl_spinlock_wait
        absl_hash
        absl_city
        absl_wyhash
        absl_bad_variant_access
        yaml-cppd)