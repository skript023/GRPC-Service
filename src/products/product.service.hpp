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
using grpc::ServerWriter;

namespace microservice
{
    class ProductService final : public Product::Service
    {
        Status FindAllProduct(ServerContext* context, const EmptyRequest* request, ServerWriter<::product::ProductsReply>* reply) override;
        Status FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply) override;
        Status CreateProduct(ServerContext* context, const CreateRequest* request, QueryReply* reply) override;
        Status UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply) override;
        Status RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* reply) override;
        bool on_changed(std::vector<std::string>& previousState);
    private:
        std::string m_string;
        std::vector <std::string> m_mock_data
        {
            "Product A",
            "Product B",
            "Product C",
        };

        std::atomic<bool> m_stream = true;
        ProductsReply m_reply;
    };
}