cmake_minimum_required(VERSION 3.20)

project(vs-grpc)
#set(CMAKE_CXX_FLAGS "-m32")
set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
# 头文件
set(THIRD_PARTY_DIR ./thirdparty)
set(GRPC_INCLUDE D:\\work\\cpp_lib\\grpclib\\grpc32\\grpc\\include)
set(PROTO_INCLUDE ./proto)
set(INCLUDE ./include)
set(BOOST_INCLUDE D:\\work\\cpp_lib\\boost_1_70_0)
include_directories(${GRPC_INCLUDE} ${PROTO_INCLUDE} ${THIRD_PARTY_DIR} ${BOOST_INCLUDE} ${INCLUDE} ${YAML_INCLUDE})

# 库文件
set(GRPC_LIB D:\\work\\cpp_lib\\grpclib\\grpc32\\grpc\\lib)
set(LIB ./lib)
set(BOOST_LIB D:\\work\\cpp_lib\\boost_1_70_0\\stage\\lib)
link_directories(${GRPC_LIB} ${LIB} ${BOOST_LIB})


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
        )