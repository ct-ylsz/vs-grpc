// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: vs.proto

#include "vs.pb.h"
#include "vs.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace vs {

static const char* VsService_method_names[] = {
  "/vs.VsService/TagValuesGet",
  "/vs.VsService/TagFeatureGet",
  "/vs.VsService/TagTimeSection",
  "/vs.VsService/TagDescGet",
  "/vs.VsService/DbPing",
  "/vs.VsService/TagCountByRangeGet",
  "/vs.VsService/TagListGet",
  "/vs.VsService/TagValuesByCountGet",
  "/vs.VsService/ServiceStop",
  "/vs.VsService/TagSnapshotValue",
  "/vs.VsService/TagFractureSectionGet",
  "/vs.VsService/TagAppendRTTagDataByBatch",
};

std::unique_ptr< VsService::Stub> VsService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< VsService::Stub> stub(new VsService::Stub(channel, options));
  return stub;
}

VsService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_TagValuesGet_(VsService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagFeatureGet_(VsService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagTimeSection_(VsService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagDescGet_(VsService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DbPing_(VsService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagCountByRangeGet_(VsService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagListGet_(VsService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagValuesByCountGet_(VsService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ServiceStop_(VsService_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagSnapshotValue_(VsService_method_names[9], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagFractureSectionGet_(VsService_method_names[10], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_TagAppendRTTagDataByBatch_(VsService_method_names[11], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status VsService::Stub::TagValuesGet(::grpc::ClientContext* context, const ::vs::TagValuesGetReq& request, ::vs::TagValuesGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagValuesGetReq, ::vs::TagValuesGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagValuesGet_, context, request, response);
}

void VsService::Stub::async::TagValuesGet(::grpc::ClientContext* context, const ::vs::TagValuesGetReq* request, ::vs::TagValuesGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagValuesGetReq, ::vs::TagValuesGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagValuesGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagValuesGet(::grpc::ClientContext* context, const ::vs::TagValuesGetReq* request, ::vs::TagValuesGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagValuesGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagValuesGetResp>* VsService::Stub::PrepareAsyncTagValuesGetRaw(::grpc::ClientContext* context, const ::vs::TagValuesGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagValuesGetResp, ::vs::TagValuesGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagValuesGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagValuesGetResp>* VsService::Stub::AsyncTagValuesGetRaw(::grpc::ClientContext* context, const ::vs::TagValuesGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagValuesGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagFeatureGet(::grpc::ClientContext* context, const ::vs::TagFeatureGetReq& request, ::vs::TagFeatureGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagFeatureGetReq, ::vs::TagFeatureGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagFeatureGet_, context, request, response);
}

void VsService::Stub::async::TagFeatureGet(::grpc::ClientContext* context, const ::vs::TagFeatureGetReq* request, ::vs::TagFeatureGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagFeatureGetReq, ::vs::TagFeatureGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagFeatureGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagFeatureGet(::grpc::ClientContext* context, const ::vs::TagFeatureGetReq* request, ::vs::TagFeatureGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagFeatureGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagFeatureGetResp>* VsService::Stub::PrepareAsyncTagFeatureGetRaw(::grpc::ClientContext* context, const ::vs::TagFeatureGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagFeatureGetResp, ::vs::TagFeatureGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagFeatureGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagFeatureGetResp>* VsService::Stub::AsyncTagFeatureGetRaw(::grpc::ClientContext* context, const ::vs::TagFeatureGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagFeatureGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagTimeSection(::grpc::ClientContext* context, const ::vs::TagTimeSectionReq& request, ::vs::TagTimeSectionResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagTimeSectionReq, ::vs::TagTimeSectionResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagTimeSection_, context, request, response);
}

void VsService::Stub::async::TagTimeSection(::grpc::ClientContext* context, const ::vs::TagTimeSectionReq* request, ::vs::TagTimeSectionResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagTimeSectionReq, ::vs::TagTimeSectionResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagTimeSection_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagTimeSection(::grpc::ClientContext* context, const ::vs::TagTimeSectionReq* request, ::vs::TagTimeSectionResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagTimeSection_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagTimeSectionResp>* VsService::Stub::PrepareAsyncTagTimeSectionRaw(::grpc::ClientContext* context, const ::vs::TagTimeSectionReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagTimeSectionResp, ::vs::TagTimeSectionReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagTimeSection_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagTimeSectionResp>* VsService::Stub::AsyncTagTimeSectionRaw(::grpc::ClientContext* context, const ::vs::TagTimeSectionReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagTimeSectionRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagDescGet(::grpc::ClientContext* context, const ::vs::TagDescGetReq& request, ::vs::TagDescGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagDescGetReq, ::vs::TagDescGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagDescGet_, context, request, response);
}

void VsService::Stub::async::TagDescGet(::grpc::ClientContext* context, const ::vs::TagDescGetReq* request, ::vs::TagDescGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagDescGetReq, ::vs::TagDescGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagDescGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagDescGet(::grpc::ClientContext* context, const ::vs::TagDescGetReq* request, ::vs::TagDescGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagDescGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagDescGetResp>* VsService::Stub::PrepareAsyncTagDescGetRaw(::grpc::ClientContext* context, const ::vs::TagDescGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagDescGetResp, ::vs::TagDescGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagDescGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagDescGetResp>* VsService::Stub::AsyncTagDescGetRaw(::grpc::ClientContext* context, const ::vs::TagDescGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagDescGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::DbPing(::grpc::ClientContext* context, const ::vs::DbPingReq& request, ::vs::DbPingResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::DbPingReq, ::vs::DbPingResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DbPing_, context, request, response);
}

void VsService::Stub::async::DbPing(::grpc::ClientContext* context, const ::vs::DbPingReq* request, ::vs::DbPingResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::DbPingReq, ::vs::DbPingResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DbPing_, context, request, response, std::move(f));
}

void VsService::Stub::async::DbPing(::grpc::ClientContext* context, const ::vs::DbPingReq* request, ::vs::DbPingResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DbPing_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::DbPingResp>* VsService::Stub::PrepareAsyncDbPingRaw(::grpc::ClientContext* context, const ::vs::DbPingReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::DbPingResp, ::vs::DbPingReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DbPing_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::DbPingResp>* VsService::Stub::AsyncDbPingRaw(::grpc::ClientContext* context, const ::vs::DbPingReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDbPingRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagCountByRangeGet(::grpc::ClientContext* context, const ::vs::TagCountByRangeGetReq& request, ::vs::TagCountByRangeGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagCountByRangeGetReq, ::vs::TagCountByRangeGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagCountByRangeGet_, context, request, response);
}

void VsService::Stub::async::TagCountByRangeGet(::grpc::ClientContext* context, const ::vs::TagCountByRangeGetReq* request, ::vs::TagCountByRangeGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagCountByRangeGetReq, ::vs::TagCountByRangeGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagCountByRangeGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagCountByRangeGet(::grpc::ClientContext* context, const ::vs::TagCountByRangeGetReq* request, ::vs::TagCountByRangeGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagCountByRangeGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagCountByRangeGetResp>* VsService::Stub::PrepareAsyncTagCountByRangeGetRaw(::grpc::ClientContext* context, const ::vs::TagCountByRangeGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagCountByRangeGetResp, ::vs::TagCountByRangeGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagCountByRangeGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagCountByRangeGetResp>* VsService::Stub::AsyncTagCountByRangeGetRaw(::grpc::ClientContext* context, const ::vs::TagCountByRangeGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagCountByRangeGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagListGet(::grpc::ClientContext* context, const ::vs::TagListGetReq& request, ::vs::TagListGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagListGetReq, ::vs::TagListGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagListGet_, context, request, response);
}

void VsService::Stub::async::TagListGet(::grpc::ClientContext* context, const ::vs::TagListGetReq* request, ::vs::TagListGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagListGetReq, ::vs::TagListGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagListGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagListGet(::grpc::ClientContext* context, const ::vs::TagListGetReq* request, ::vs::TagListGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagListGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagListGetResp>* VsService::Stub::PrepareAsyncTagListGetRaw(::grpc::ClientContext* context, const ::vs::TagListGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagListGetResp, ::vs::TagListGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagListGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagListGetResp>* VsService::Stub::AsyncTagListGetRaw(::grpc::ClientContext* context, const ::vs::TagListGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagListGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagValuesByCountGet(::grpc::ClientContext* context, const ::vs::TagValuesByCountGetReq& request, ::vs::TagValuesByCountGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagValuesByCountGetReq, ::vs::TagValuesByCountGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagValuesByCountGet_, context, request, response);
}

void VsService::Stub::async::TagValuesByCountGet(::grpc::ClientContext* context, const ::vs::TagValuesByCountGetReq* request, ::vs::TagValuesByCountGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagValuesByCountGetReq, ::vs::TagValuesByCountGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagValuesByCountGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagValuesByCountGet(::grpc::ClientContext* context, const ::vs::TagValuesByCountGetReq* request, ::vs::TagValuesByCountGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagValuesByCountGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagValuesByCountGetResp>* VsService::Stub::PrepareAsyncTagValuesByCountGetRaw(::grpc::ClientContext* context, const ::vs::TagValuesByCountGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagValuesByCountGetResp, ::vs::TagValuesByCountGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagValuesByCountGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagValuesByCountGetResp>* VsService::Stub::AsyncTagValuesByCountGetRaw(::grpc::ClientContext* context, const ::vs::TagValuesByCountGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagValuesByCountGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::ServiceStop(::grpc::ClientContext* context, const ::vs::ServiceStopReq& request, ::vs::ServiceStopResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::ServiceStopReq, ::vs::ServiceStopResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ServiceStop_, context, request, response);
}

void VsService::Stub::async::ServiceStop(::grpc::ClientContext* context, const ::vs::ServiceStopReq* request, ::vs::ServiceStopResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::ServiceStopReq, ::vs::ServiceStopResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ServiceStop_, context, request, response, std::move(f));
}

void VsService::Stub::async::ServiceStop(::grpc::ClientContext* context, const ::vs::ServiceStopReq* request, ::vs::ServiceStopResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ServiceStop_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::ServiceStopResp>* VsService::Stub::PrepareAsyncServiceStopRaw(::grpc::ClientContext* context, const ::vs::ServiceStopReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::ServiceStopResp, ::vs::ServiceStopReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ServiceStop_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::ServiceStopResp>* VsService::Stub::AsyncServiceStopRaw(::grpc::ClientContext* context, const ::vs::ServiceStopReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncServiceStopRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagSnapshotValue(::grpc::ClientContext* context, const ::vs::TagSnapshotValueReq& request, ::vs::TagSnapshotValueResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagSnapshotValueReq, ::vs::TagSnapshotValueResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagSnapshotValue_, context, request, response);
}

void VsService::Stub::async::TagSnapshotValue(::grpc::ClientContext* context, const ::vs::TagSnapshotValueReq* request, ::vs::TagSnapshotValueResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagSnapshotValueReq, ::vs::TagSnapshotValueResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagSnapshotValue_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagSnapshotValue(::grpc::ClientContext* context, const ::vs::TagSnapshotValueReq* request, ::vs::TagSnapshotValueResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagSnapshotValue_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagSnapshotValueResp>* VsService::Stub::PrepareAsyncTagSnapshotValueRaw(::grpc::ClientContext* context, const ::vs::TagSnapshotValueReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagSnapshotValueResp, ::vs::TagSnapshotValueReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagSnapshotValue_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagSnapshotValueResp>* VsService::Stub::AsyncTagSnapshotValueRaw(::grpc::ClientContext* context, const ::vs::TagSnapshotValueReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagSnapshotValueRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagFractureSectionGet(::grpc::ClientContext* context, const ::vs::TagFractureSectionGetReq& request, ::vs::TagFractureSectionGetResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagFractureSectionGetReq, ::vs::TagFractureSectionGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagFractureSectionGet_, context, request, response);
}

void VsService::Stub::async::TagFractureSectionGet(::grpc::ClientContext* context, const ::vs::TagFractureSectionGetReq* request, ::vs::TagFractureSectionGetResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagFractureSectionGetReq, ::vs::TagFractureSectionGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagFractureSectionGet_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagFractureSectionGet(::grpc::ClientContext* context, const ::vs::TagFractureSectionGetReq* request, ::vs::TagFractureSectionGetResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagFractureSectionGet_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagFractureSectionGetResp>* VsService::Stub::PrepareAsyncTagFractureSectionGetRaw(::grpc::ClientContext* context, const ::vs::TagFractureSectionGetReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagFractureSectionGetResp, ::vs::TagFractureSectionGetReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagFractureSectionGet_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagFractureSectionGetResp>* VsService::Stub::AsyncTagFractureSectionGetRaw(::grpc::ClientContext* context, const ::vs::TagFractureSectionGetReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagFractureSectionGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VsService::Stub::TagAppendRTTagDataByBatch(::grpc::ClientContext* context, const ::vs::TagAppendRTTagDataByBatchReq& request, ::vs::TagAppendRTTagDataByBatchResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vs::TagAppendRTTagDataByBatchReq, ::vs::TagAppendRTTagDataByBatchResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_TagAppendRTTagDataByBatch_, context, request, response);
}

void VsService::Stub::async::TagAppendRTTagDataByBatch(::grpc::ClientContext* context, const ::vs::TagAppendRTTagDataByBatchReq* request, ::vs::TagAppendRTTagDataByBatchResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vs::TagAppendRTTagDataByBatchReq, ::vs::TagAppendRTTagDataByBatchResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagAppendRTTagDataByBatch_, context, request, response, std::move(f));
}

void VsService::Stub::async::TagAppendRTTagDataByBatch(::grpc::ClientContext* context, const ::vs::TagAppendRTTagDataByBatchReq* request, ::vs::TagAppendRTTagDataByBatchResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_TagAppendRTTagDataByBatch_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vs::TagAppendRTTagDataByBatchResp>* VsService::Stub::PrepareAsyncTagAppendRTTagDataByBatchRaw(::grpc::ClientContext* context, const ::vs::TagAppendRTTagDataByBatchReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vs::TagAppendRTTagDataByBatchResp, ::vs::TagAppendRTTagDataByBatchReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_TagAppendRTTagDataByBatch_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vs::TagAppendRTTagDataByBatchResp>* VsService::Stub::AsyncTagAppendRTTagDataByBatchRaw(::grpc::ClientContext* context, const ::vs::TagAppendRTTagDataByBatchReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncTagAppendRTTagDataByBatchRaw(context, request, cq);
  result->StartCall();
  return result;
}

VsService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagValuesGetReq, ::vs::TagValuesGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagValuesGetReq* req,
             ::vs::TagValuesGetResp* resp) {
               return service->TagValuesGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagFeatureGetReq, ::vs::TagFeatureGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagFeatureGetReq* req,
             ::vs::TagFeatureGetResp* resp) {
               return service->TagFeatureGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagTimeSectionReq, ::vs::TagTimeSectionResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagTimeSectionReq* req,
             ::vs::TagTimeSectionResp* resp) {
               return service->TagTimeSection(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagDescGetReq, ::vs::TagDescGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagDescGetReq* req,
             ::vs::TagDescGetResp* resp) {
               return service->TagDescGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::DbPingReq, ::vs::DbPingResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::DbPingReq* req,
             ::vs::DbPingResp* resp) {
               return service->DbPing(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagCountByRangeGetReq, ::vs::TagCountByRangeGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagCountByRangeGetReq* req,
             ::vs::TagCountByRangeGetResp* resp) {
               return service->TagCountByRangeGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagListGetReq, ::vs::TagListGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagListGetReq* req,
             ::vs::TagListGetResp* resp) {
               return service->TagListGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagValuesByCountGetReq, ::vs::TagValuesByCountGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagValuesByCountGetReq* req,
             ::vs::TagValuesByCountGetResp* resp) {
               return service->TagValuesByCountGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::ServiceStopReq, ::vs::ServiceStopResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::ServiceStopReq* req,
             ::vs::ServiceStopResp* resp) {
               return service->ServiceStop(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[9],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagSnapshotValueReq, ::vs::TagSnapshotValueResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagSnapshotValueReq* req,
             ::vs::TagSnapshotValueResp* resp) {
               return service->TagSnapshotValue(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[10],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagFractureSectionGetReq, ::vs::TagFractureSectionGetResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagFractureSectionGetReq* req,
             ::vs::TagFractureSectionGetResp* resp) {
               return service->TagFractureSectionGet(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VsService_method_names[11],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VsService::Service, ::vs::TagAppendRTTagDataByBatchReq, ::vs::TagAppendRTTagDataByBatchResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VsService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vs::TagAppendRTTagDataByBatchReq* req,
             ::vs::TagAppendRTTagDataByBatchResp* resp) {
               return service->TagAppendRTTagDataByBatch(ctx, req, resp);
             }, this)));
}

VsService::Service::~Service() {
}

::grpc::Status VsService::Service::TagValuesGet(::grpc::ServerContext* context, const ::vs::TagValuesGetReq* request, ::vs::TagValuesGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagFeatureGet(::grpc::ServerContext* context, const ::vs::TagFeatureGetReq* request, ::vs::TagFeatureGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagTimeSection(::grpc::ServerContext* context, const ::vs::TagTimeSectionReq* request, ::vs::TagTimeSectionResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagDescGet(::grpc::ServerContext* context, const ::vs::TagDescGetReq* request, ::vs::TagDescGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::DbPing(::grpc::ServerContext* context, const ::vs::DbPingReq* request, ::vs::DbPingResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagCountByRangeGet(::grpc::ServerContext* context, const ::vs::TagCountByRangeGetReq* request, ::vs::TagCountByRangeGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagListGet(::grpc::ServerContext* context, const ::vs::TagListGetReq* request, ::vs::TagListGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagValuesByCountGet(::grpc::ServerContext* context, const ::vs::TagValuesByCountGetReq* request, ::vs::TagValuesByCountGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::ServiceStop(::grpc::ServerContext* context, const ::vs::ServiceStopReq* request, ::vs::ServiceStopResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagSnapshotValue(::grpc::ServerContext* context, const ::vs::TagSnapshotValueReq* request, ::vs::TagSnapshotValueResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagFractureSectionGet(::grpc::ServerContext* context, const ::vs::TagFractureSectionGetReq* request, ::vs::TagFractureSectionGetResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VsService::Service::TagAppendRTTagDataByBatch(::grpc::ServerContext* context, const ::vs::TagAppendRTTagDataByBatchReq* request, ::vs::TagAppendRTTagDataByBatchResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace vs

