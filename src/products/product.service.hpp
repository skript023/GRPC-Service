#pragma once
#include "common.hpp"
#include "service_invoker.hpp"
#include "entity/product.entity.hpp"

#include "protobuf/product.grpc.pb.h"

using product::Product;

using product::ProductReply;
using product::QueryReply;
using product::ProductsReply;

using product::FindByIdRequest;
using product::EmptyRequest;
using product::UpdateRequest;
using product::CreateRequest;

using grpc::ServerWriter;
using grpc::ServerReaderWriter;
using grpc::ServerReader;

namespace microservice
{
    using product_table_t = std::vector<microservice::Products, std::allocator<microservice::Products>>; 
    class ProductService final : public Product::Service
    {
    private:
        Status FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply) override;
        Status FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply) override;
        Status CreateProduct(ServerContext* context, const CreateRequest* request, QueryReply* reply) override;
        Status UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply) override;
        Status RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* reply) override;

        Status FindAllProductStream(ServerContext* context, const EmptyRequest* request, ServerWriter<ProductsReply>* reply) override;
        Status UpdateProductStream(ServerContext* context, ServerReader<UpdateRequest>* reader, QueryReply* response) override;


        Status CreateProductBidiStream(ServerContext* context, ServerReaderWriter<QueryReply, CreateRequest>* stream) override;
    private:
        bool on_changed(product_table_t& previousState, product_table_t const& currentState);
        bool does_exist(std::string const& element);
    private:
        std::string m_string;
        std::atomic<bool> m_stream;
        ProductsReply m_reply;
        std::mutex m_mutex;
    private:
        std::vector <std::string> m_mock_data
        {
            "Product A",
            "Product B",
            "Product C",
        };
    };
}