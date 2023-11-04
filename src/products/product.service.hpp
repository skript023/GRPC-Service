#pragma once
#include "common.hpp"
#include "service_invoker.hpp"

#include "protobuf/product.grpc.pb.h"

using product::Product;

using product::ProductReply;
using product::QueryReply;
using product::ProductsReply;

using product::FindByIdRequest;
using product::EmptyRequest;
using product::UpdateRequest;
using product::CreateRequest;
using product::ProductsReply;
using grpc::ServerAsyncWriter;

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
        std::vector<ProductReply> m_mock_data;
        std::vector<products> m_products = {
            {1, "Product A"},
            {2, "Product B"},
            {3, "Product C"},
        };

        void populate_data()
        {
            ProductReply dt;
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
        product_service(Product::AsyncService* service, ServerCompletionQueue* cq);
        virtual void proceed() override;
        product_service* find_all_begin();
        product_service* find_all_end();
    private:
        Product::AsyncService* m_service;
        ServerCompletionQueue* m_completed_queue;
        ServerContext m_context;
        EmptyRequest m_request;
        ProductsReply m_reply;
        ServerAsyncWriter<ProductsReply> m_responder;
        CallStatus m_status;  // The current serving state.
    };
}