#pragma once
#include "common.hpp"
#include "service_invoker.hpp"

#include "protobuf/helloworld.grpc.pb.h"

using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

namespace microservice
{
    // Class encompasing the state and logic needed to serve a request.
    class GreeterService final : public Greeter::Service 
    {
        Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override;
    };
}