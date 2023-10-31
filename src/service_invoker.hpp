#pragma once
#include "common.hpp"
#include "greeter/greeter.service.hpp"

namespace microservice
{
    // Class encompasing the state and logic needed to serve a request.
    class register_service
    {
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        register_service(Greeter::AsyncService* service, ServerCompletionQueue* cq);

        void proceed();

    private:
        // The means of communication with the gRPC runtime for an asynchronous
        // server.
        Greeter::AsyncService* m_service;
        // The producer-consumer queue where for asynchronous server notifications.
        ServerCompletionQueue* m_completed_queue;
        // Context for the rpc, allowing to tweak aspects of it such as the use
        // of compression, authentication, as well as to send metadata back to the
        // client.
        ServerContext m_context;

        // What we get from the client.
        HelloRequest m_request;
        // What we send back to the client.
        HelloReply m_reply;

        // The means to get back to the client.
        ServerAsyncResponseWriter<HelloReply> m_responder;

        // Let's implement a tiny state machine with the following states.
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus m_status;  // The current serving state.
    };
}