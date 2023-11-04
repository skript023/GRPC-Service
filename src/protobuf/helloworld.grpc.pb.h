// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: helloworld.proto
// Original file comments:
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_helloworld_2eproto__INCLUDED
#define GRPC_helloworld_2eproto__INCLUDED

#include "helloworld.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace helloworld {

// The greeting service definition.
class Greeter final {
 public:
  static constexpr char const* service_full_name() {
    return "helloworld.Greeter";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Sends a greeting
    virtual ::grpc::Status SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::helloworld::HelloReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>> AsyncSayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>>(AsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>> PrepareAsyncSayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>>(PrepareAsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderInterface< ::helloworld::HelloReply>> SayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::helloworld::HelloReply>>(SayHelloStreamReplyRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>> AsyncSayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>>(AsyncSayHelloStreamReplyRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>> PrepareAsyncSayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>>(PrepareAsyncSayHelloStreamReplyRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>> SayHelloBidiStream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(SayHelloBidiStreamRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>> AsyncSayHelloBidiStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(AsyncSayHelloBidiStreamRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>> PrepareAsyncSayHelloBidiStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(PrepareAsyncSayHelloBidiStreamRaw(context, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // Sends a greeting
      virtual void SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void SayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::grpc::ClientReadReactor< ::helloworld::HelloReply>* reactor) = 0;
      virtual void SayHelloBidiStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::helloworld::HelloRequest,::helloworld::HelloReply>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>* AsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::helloworld::HelloReply>* PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderInterface< ::helloworld::HelloReply>* SayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>* AsyncSayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::helloworld::HelloReply>* PrepareAsyncSayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>* SayHelloBidiStreamRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>* AsyncSayHelloBidiStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::helloworld::HelloRequest, ::helloworld::HelloReply>* PrepareAsyncSayHelloBidiStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::helloworld::HelloReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>> AsyncSayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>>(AsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>> PrepareAsyncSayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>>(PrepareAsyncSayHelloRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReader< ::helloworld::HelloReply>> SayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::helloworld::HelloReply>>(SayHelloStreamReplyRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::helloworld::HelloReply>> AsyncSayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::helloworld::HelloReply>>(AsyncSayHelloStreamReplyRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::helloworld::HelloReply>> PrepareAsyncSayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::helloworld::HelloReply>>(PrepareAsyncSayHelloStreamReplyRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>> SayHelloBidiStream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(SayHelloBidiStreamRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>> AsyncSayHelloBidiStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(AsyncSayHelloBidiStreamRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>> PrepareAsyncSayHelloBidiStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>>(PrepareAsyncSayHelloBidiStreamRaw(context, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response, std::function<void(::grpc::Status)>) override;
      void SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      void SayHelloStreamReply(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::grpc::ClientReadReactor< ::helloworld::HelloReply>* reactor) override;
      void SayHelloBidiStream(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::helloworld::HelloRequest,::helloworld::HelloReply>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>* AsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>* PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReader< ::helloworld::HelloReply>* SayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request) override;
    ::grpc::ClientAsyncReader< ::helloworld::HelloReply>* AsyncSayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::helloworld::HelloReply>* PrepareAsyncSayHelloStreamReplyRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>* SayHelloBidiStreamRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>* AsyncSayHelloBidiStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::helloworld::HelloRequest, ::helloworld::HelloReply>* PrepareAsyncSayHelloBidiStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SayHello_;
    const ::grpc::internal::RpcMethod rpcmethod_SayHelloStreamReply_;
    const ::grpc::internal::RpcMethod rpcmethod_SayHelloBidiStream_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Sends a greeting
    virtual ::grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response);
    virtual ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::grpc::ServerWriter< ::helloworld::HelloReply>* writer);
    virtual ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SayHello() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHello(::grpc::ServerContext* context, ::helloworld::HelloRequest* request, ::grpc::ServerAsyncResponseWriter< ::helloworld::HelloReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHelloStreamReply(::grpc::ServerContext* context, ::helloworld::HelloRequest* request, ::grpc::ServerAsyncWriter< ::helloworld::HelloReply>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SayHelloBidiStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SayHelloBidiStream() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_SayHelloBidiStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHelloBidiStream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(2, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SayHello<WithAsyncMethod_SayHelloStreamReply<WithAsyncMethod_SayHelloBidiStream<Service > > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SayHello() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::helloworld::HelloRequest, ::helloworld::HelloReply>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response) { return this->SayHello(context, request, response); }));}
    void SetMessageAllocatorFor_SayHello(
        ::grpc::MessageAllocator< ::helloworld::HelloRequest, ::helloworld::HelloReply>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::helloworld::HelloRequest, ::helloworld::HelloReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SayHello(
      ::grpc::CallbackServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackServerStreamingHandler< ::helloworld::HelloRequest, ::helloworld::HelloReply>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::helloworld::HelloRequest* request) { return this->SayHelloStreamReply(context, request); }));
    }
    ~WithCallbackMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::helloworld::HelloReply>* SayHelloStreamReply(
      ::grpc::CallbackServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_SayHelloBidiStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SayHelloBidiStream() {
      ::grpc::Service::MarkMethodCallback(2,
          new ::grpc::internal::CallbackBidiHandler< ::helloworld::HelloRequest, ::helloworld::HelloReply>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->SayHelloBidiStream(context); }));
    }
    ~WithCallbackMethod_SayHelloBidiStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::helloworld::HelloRequest, ::helloworld::HelloReply>* SayHelloBidiStream(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef WithCallbackMethod_SayHello<WithCallbackMethod_SayHelloStreamReply<WithCallbackMethod_SayHelloBidiStream<Service > > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SayHello() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SayHelloBidiStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SayHelloBidiStream() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_SayHelloBidiStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SayHello() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHello(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHelloStreamReply(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(1, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_SayHelloBidiStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SayHelloBidiStream() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_SayHelloBidiStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSayHelloBidiStream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(2, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SayHello() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SayHello(context, request, response); }));
    }
    ~WithRawCallbackMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* SayHello(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const::grpc::ByteBuffer* request) { return this->SayHelloStreamReply(context, request); }));
    }
    ~WithRawCallbackMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* SayHelloStreamReply(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SayHelloBidiStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SayHelloBidiStream() {
      ::grpc::Service::MarkMethodRawCallback(2,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->SayHelloBidiStream(context); }));
    }
    ~WithRawCallbackMethod_SayHelloBidiStream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SayHelloBidiStream(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::helloworld::HelloReply, ::helloworld::HelloRequest>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* SayHelloBidiStream(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SayHello : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SayHello() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::helloworld::HelloRequest, ::helloworld::HelloReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::helloworld::HelloRequest, ::helloworld::HelloReply>* streamer) {
                       return this->StreamedSayHello(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SayHello() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SayHello(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::helloworld::HelloReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSayHello(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::helloworld::HelloRequest,::helloworld::HelloReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SayHello<Service > StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_SayHelloStreamReply : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_SayHelloStreamReply() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::helloworld::HelloRequest, ::helloworld::HelloReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerSplitStreamer<
                     ::helloworld::HelloRequest, ::helloworld::HelloReply>* streamer) {
                       return this->StreamedSayHelloStreamReply(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_SayHelloStreamReply() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SayHelloStreamReply(::grpc::ServerContext* /*context*/, const ::helloworld::HelloRequest* /*request*/, ::grpc::ServerWriter< ::helloworld::HelloReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedSayHelloStreamReply(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::helloworld::HelloRequest,::helloworld::HelloReply>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_SayHelloStreamReply<Service > SplitStreamedService;
  typedef WithStreamedUnaryMethod_SayHello<WithSplitStreamingMethod_SayHelloStreamReply<Service > > StreamedService;
};

}  // namespace helloworld


#endif  // GRPC_helloworld_2eproto__INCLUDED
