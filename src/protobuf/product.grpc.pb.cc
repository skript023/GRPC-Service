// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: product.proto

#include "product.pb.h"
#include "product.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace product {

static const char* Product_method_names[] = {
  "/product.Product/FindAllProduct",
  "/product.Product/FindOneProduct",
  "/product.Product/CreateProduct",
  "/product.Product/UpdateProduct",
  "/product.Product/RemoveProduct",
  "/product.Product/QueryProduct",
};

std::unique_ptr< Product::Stub> Product::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Product::Stub> stub(new Product::Stub(channel, options));
  return stub;
}

Product::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_FindAllProduct_(Product_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_FindOneProduct_(Product_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CreateProduct_(Product_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateProduct_(Product_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RemoveProduct_(Product_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_QueryProduct_(Product_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::Status Product::Stub::FindAllProduct(::grpc::ClientContext* context, const ::product::EmptyRequest& request, ::product::ProductsReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::product::EmptyRequest, ::product::ProductsReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_FindAllProduct_, context, request, response);
}

void Product::Stub::async::FindAllProduct(::grpc::ClientContext* context, const ::product::EmptyRequest* request, ::product::ProductsReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::product::EmptyRequest, ::product::ProductsReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FindAllProduct_, context, request, response, std::move(f));
}

void Product::Stub::async::FindAllProduct(::grpc::ClientContext* context, const ::product::EmptyRequest* request, ::product::ProductsReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FindAllProduct_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::product::ProductsReply>* Product::Stub::PrepareAsyncFindAllProductRaw(::grpc::ClientContext* context, const ::product::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::product::ProductsReply, ::product::EmptyRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_FindAllProduct_, context, request);
}

::grpc::ClientAsyncResponseReader< ::product::ProductsReply>* Product::Stub::AsyncFindAllProductRaw(::grpc::ClientContext* context, const ::product::EmptyRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncFindAllProductRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Product::Stub::FindOneProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::product::ProductReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_FindOneProduct_, context, request, response);
}

void Product::Stub::async::FindOneProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FindOneProduct_, context, request, response, std::move(f));
}

void Product::Stub::async::FindOneProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_FindOneProduct_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::PrepareAsyncFindOneProductRaw(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::product::ProductReply, ::product::FindByIdRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_FindOneProduct_, context, request);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::AsyncFindOneProductRaw(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncFindOneProductRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Product::Stub::CreateProduct(::grpc::ClientContext* context, const ::product::CreateRequest& request, ::product::ProductReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::product::CreateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CreateProduct_, context, request, response);
}

void Product::Stub::async::CreateProduct(::grpc::ClientContext* context, const ::product::CreateRequest* request, ::product::ProductReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::product::CreateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateProduct_, context, request, response, std::move(f));
}

void Product::Stub::async::CreateProduct(::grpc::ClientContext* context, const ::product::CreateRequest* request, ::product::ProductReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateProduct_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::PrepareAsyncCreateProductRaw(::grpc::ClientContext* context, const ::product::CreateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::product::ProductReply, ::product::CreateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CreateProduct_, context, request);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::AsyncCreateProductRaw(::grpc::ClientContext* context, const ::product::CreateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCreateProductRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Product::Stub::UpdateProduct(::grpc::ClientContext* context, const ::product::UpdateRequest& request, ::product::ProductReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::product::UpdateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UpdateProduct_, context, request, response);
}

void Product::Stub::async::UpdateProduct(::grpc::ClientContext* context, const ::product::UpdateRequest* request, ::product::ProductReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::product::UpdateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateProduct_, context, request, response, std::move(f));
}

void Product::Stub::async::UpdateProduct(::grpc::ClientContext* context, const ::product::UpdateRequest* request, ::product::ProductReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateProduct_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::PrepareAsyncUpdateProductRaw(::grpc::ClientContext* context, const ::product::UpdateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::product::ProductReply, ::product::UpdateRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UpdateProduct_, context, request);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::AsyncUpdateProductRaw(::grpc::ClientContext* context, const ::product::UpdateRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUpdateProductRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Product::Stub::RemoveProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::product::ProductReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_RemoveProduct_, context, request, response);
}

void Product::Stub::async::RemoveProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveProduct_, context, request, response, std::move(f));
}

void Product::Stub::async::RemoveProduct(::grpc::ClientContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_RemoveProduct_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::PrepareAsyncRemoveProductRaw(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::product::ProductReply, ::product::FindByIdRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_RemoveProduct_, context, request);
}

::grpc::ClientAsyncResponseReader< ::product::ProductReply>* Product::Stub::AsyncRemoveProductRaw(::grpc::ClientContext* context, const ::product::FindByIdRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRemoveProductRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReaderWriter< ::product::PaginationRequest, ::product::ProductReply>* Product::Stub::QueryProductRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::product::PaginationRequest, ::product::ProductReply>::Create(channel_.get(), rpcmethod_QueryProduct_, context);
}

void Product::Stub::async::QueryProduct(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::product::PaginationRequest,::product::ProductReply>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::product::PaginationRequest,::product::ProductReply>::Create(stub_->channel_.get(), stub_->rpcmethod_QueryProduct_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::product::PaginationRequest, ::product::ProductReply>* Product::Stub::AsyncQueryProductRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::product::PaginationRequest, ::product::ProductReply>::Create(channel_.get(), cq, rpcmethod_QueryProduct_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::product::PaginationRequest, ::product::ProductReply>* Product::Stub::PrepareAsyncQueryProductRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::product::PaginationRequest, ::product::ProductReply>::Create(channel_.get(), cq, rpcmethod_QueryProduct_, context, false, nullptr);
}

Product::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Product::Service, ::product::EmptyRequest, ::product::ProductsReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             const ::product::EmptyRequest* req,
             ::product::ProductsReply* resp) {
               return service->FindAllProduct(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Product::Service, ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             const ::product::FindByIdRequest* req,
             ::product::ProductReply* resp) {
               return service->FindOneProduct(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Product::Service, ::product::CreateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             const ::product::CreateRequest* req,
             ::product::ProductReply* resp) {
               return service->CreateProduct(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Product::Service, ::product::UpdateRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             const ::product::UpdateRequest* req,
             ::product::ProductReply* resp) {
               return service->UpdateProduct(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Product::Service, ::product::FindByIdRequest, ::product::ProductReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             const ::product::FindByIdRequest* req,
             ::product::ProductReply* resp) {
               return service->RemoveProduct(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Product_method_names[5],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< Product::Service, ::product::PaginationRequest, ::product::ProductReply>(
          [](Product::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::product::ProductReply,
             ::product::PaginationRequest>* stream) {
               return service->QueryProduct(ctx, stream);
             }, this)));
}

Product::Service::~Service() {
}

::grpc::Status Product::Service::FindAllProduct(::grpc::ServerContext* context, const ::product::EmptyRequest* request, ::product::ProductsReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Product::Service::FindOneProduct(::grpc::ServerContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Product::Service::CreateProduct(::grpc::ServerContext* context, const ::product::CreateRequest* request, ::product::ProductReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Product::Service::UpdateProduct(::grpc::ServerContext* context, const ::product::UpdateRequest* request, ::product::ProductReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Product::Service::RemoveProduct(::grpc::ServerContext* context, const ::product::FindByIdRequest* request, ::product::ProductReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Product::Service::QueryProduct(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::product::ProductReply, ::product::PaginationRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace product

