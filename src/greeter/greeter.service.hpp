#pragma once
#include "common.hpp"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "protobuf/helloworld.grpc.pb.h"
#endif

using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

namespace microservice
{
    // Logic and data behind the server's behavior.
    class GreeterServiceImpl final : public Greeter::Service 
    {
        Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override 
        {
            std::string prefix("Hello ");
            reply->set_message(prefix + request->name());
            return Status::OK;
        }
    };
}