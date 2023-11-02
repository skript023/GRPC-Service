#pragma once
#include "common.hpp"
#include "service_invoker.hpp"

#include "protobuf/product.grpc.pb.h"

using product::Product;

using product::ProductReply;
using product::ProductsReply;

using product::FindByIdRequest;
using product::EmptyRequest;
using product::UpdateRequest;
using product::CreateRequest;

namespace microservice
{
    class ProductService final : public Product::Service
    {
        Status FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply) override;
        Status FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply) override;
        Status UpdateProduct(ServerContext* context, const UpdateRequest* request, ProductReply* reply) override;
        Status RemoveProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply) override;

        std::vector <std::string> m_mock_data
        {
            "Product A",
            "Product B",
            "Product C",
        };
    };
}