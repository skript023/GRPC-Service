#pragma once
#include "common.hpp"
#include "service_invoker.hpp"

#include "protobuf/product.grpc.pb.h"

namespace microservice
{
    enum CallStatus { CREATE, PROCESS, FINISH };

    struct products
    {
        int id;
        std::string name;
    };

    class product_service final : public service_invoker
    {
        std::vector<product::ProductReply> m_mock_data;
        std::vector<products> m_products = {
            {1, "Product A"},
            {2, "Product B"},
            {3, "Product C"},
        };

        void populate_data()
        {
            product::ProductReply dt;
            for (auto& product : m_products)
            {
                dt.set_id(product.id); 
                dt.set_name(product.name);
                m_mock_data.push_back(dt);
            }
        }
    public:
        // Take in the "service" instance (in this case representing an asynchronous
        // server) and the completion queue "cq" used for asynchronous communication
        // with the gRPC runtime.
        product_service(product::Product::AsyncService* service, grpc::ServerCompletionQueue* cq);
        virtual void proceed() override;
        product_service* find_all_begin();
        product_service* find_all_end();
    private:
        product::Product::AsyncService* m_service;
        grpc::ServerCompletionQueue* m_completed_queue;
        grpc::ServerContext m_context;
        product::EmptyRequest m_request;
        product::ProductsReply m_reply;
        grpc::ServerAsyncWriter<product::ProductsReply> m_responder;
        CallStatus m_status;  // The current serving state.
    };
}