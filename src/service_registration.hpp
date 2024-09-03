#pragma once

#include "common.hpp"
#include "service_invoker.hpp"

namespace microservice
{
    template <typename ServiceType>
    class service_registration : public service_invoker
    {
    public:
        using RpcMethodCallback = std::function<void()>;
        using ResponseMethodCallback = std::function<void()>;

        service_registration(ServiceType service, grpc::ServerContext* context, grpc::ServerCompletionQueue* cq, RpcMethodCallback callback, ResponseMethodCallback process_callback)
            : service_(service), context_(context), cq_(cq), status_(CREATE), callback_(std::move(callback)), process_callback_(std::move(process_callback))
        {
            
        }

        void proceed() override
        {
            if (status_ == CREATE)
            {
                status_ = PROCESS;
                // Call the provided callback to request the specific RPC method
                callback_();
            }
            else if (status_ == PROCESS) 
            {
                // Process the request and send a response
                process_callback_();
            }
            else 
            {
                // Cleanup and deallocate
                GPR_ASSERT(status_ == FINISH);

                delete this;
            }
        }

    private:
        void handle_request() {
            // Handle the request processing and responder management in the callback
        }

    protected:
        ServiceType service_;
        grpc::ServerCompletionQueue* cq_;
        grpc::ServerContext* context_;
        enum CallStatus { CREATE, PROCESS, FINISH } status_;
        RpcMethodCallback callback_;
        ResponseMethodCallback process_callback_;
    };
}