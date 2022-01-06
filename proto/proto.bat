

protoc --grpc_out=./ --plugin=protoc-gen-grpc=D:\grpclib\grpc32\grpc\bin\grpc_cpp_plugin.exe *.proto
protoc --cpp_out=./ *.proto