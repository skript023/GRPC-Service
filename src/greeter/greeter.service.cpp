#include "greeter.service.hpp"

namespace microservice
{
    Status GreeterService::SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply)
    {
        std::string prefix("Hello ");
        reply->set_message(prefix + request->name());
        return Status::OK;
    }
}