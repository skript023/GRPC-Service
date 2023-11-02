#pragma once
#include "common.hpp"
#include "service_invoker.hpp"

#include "protobuf/product.grpc.pb.h"

using product::Product;
using product::ProductReply;
using product::FindByIdRequest;

namespace microservice
{
	class product_service final : public service_invoker
	{
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        product_service(Product::AsyncService* service, ServerCompletionQueue* cq);
        virtual void proceed() override;
    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        Product::AsyncService* m_service;
        // The producer-consumer queue where for asynchronous server notifications.
        ServerCompletionQueue* m_completed_queue;
        // Context for the rpc, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        ServerContext m_context;

        // What we get from the client.
        FindByIdRequest m_request;
        // What we send back to the client.
        ProductReply m_reply;

        // The means to get back to the client.
        ServerAsyncResponseWriter<ProductReply> m_responder;

        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus m_status;  // The current serving state.
	};
}