#pragma once

#include "common.hpp"
#include "service_registration.hpp"

#include "protobuf/user.grpc.pb.h"

namespace microservice
{
    using user::User;

    using user::UserReply;
    using user::QueryReply;
    using user::UsersReply;

    using user::FindByIdRequest;
    using user::EmptyRequest;
    using user::UpdateRequest;
    using user::CreateRequest;
    using user::UsersReply;
    using grpc::ServerAsyncWriter;

    class user_service 
    {
    public:
        user_service(User::AsyncService* service, grpc::ServerCompletionQueue* cq)
            : service_(service), cq_(cq), responder_(&context_), client_stream_responder_(&context_), bidistream_responder_(&context_)
        {
            register_handler();
        }

        void register_handler()
        {
            handlers_.emplace_back(new service_registration(
                service_, &context_, cq_,
                [this]() {
                    service_->RequestFindAllUser(&context_, &request_, &responder_, cq_, cq_, this);
                },
                [this]() {
                    // Handle the response
                    UsersReply reply;
                    responder_.Finish(reply, grpc::Status::OK, this);
                }
            ));

            handlers_.emplace_back(new service_registration(
                service_, &context_, cq_,
                [this]() {
                    service_->RequestFindAllUserServerStream(&context_, &request_, &client_stream_responder_, cq_, cq_, this);
                },
                [this]() {
                    // Handle streaming response logic here
                    UsersReply reply;
                    client_stream_responder_.Write(reply, this);
                    client_stream_responder_.Finish(grpc::Status::OK, this);
                }
            ));

            handlers_.emplace_back(new service_registration(service_, &context_, cq_,
                [this]() {
                    service_->RequestFindOneUserBidistream(&context_, &bidistream_responder_, cq_, cq_, this);
                },
                [this]() {
                    // Handle bidirectional streaming logic here
                    UserReply reply;
                    reply.set_id(1);
                    reply.set_name("test");
                    bidistream_responder_.Write(reply, this);
                    bidistream_responder_.Finish(grpc::Status::OK, this);
                }
            ));
        }
    private:
        User::AsyncService* service_;
        grpc::ServerContext context_;
        EmptyRequest request_;
        grpc::ServerAsyncResponseWriter<UsersReply> responder_;
        grpc::ServerAsyncWriter<UsersReply> client_stream_responder_;
        grpc::ServerAsyncReaderWriter<UserReply, FindByIdRequest> bidistream_responder_;
        grpc::ServerCompletionQueue* cq_;
        std::vector<std::unique_ptr<service_invoker>> handlers_;
    };
}