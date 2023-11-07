#pragma once
#include "common.hpp"
#include "entity/product.entity.hpp"

#include "protobuf/product.grpc.pb.h"

using namespace grpc;

namespace microservice
{
    using product_table_t = std::vector<microservice::Products, std::allocator<microservice::Products>>; 
    using proto_table_t = google::protobuf::RepeatedPtrField<std::string>; 
    
    class ProductService final : public product::Product::Service
    {
    private:
        Status FindAllProduct(ServerContext* context, const product::EmptyRequest* request, product::ProductsReply* reply) override;
        Status FindOneProduct(ServerContext* context, const product::FindByIdRequest* request, product::ProductReply* reply) override;
        Status CreateProduct(ServerContext* context, const product::CreateRequest* request, product::QueryReply* reply) override;
        Status UpdateProduct(ServerContext* context, const product::UpdateRequest* request, product::QueryReply* reply) override;
        Status RemoveProduct(ServerContext* context, const product::FindByIdRequest* request, product::QueryReply* reply) override;

        Status FindAllProductStream(ServerContext* context, const product::EmptyRequest* request, ServerWriter<product::ProductsReply>* reply) override;
        Status UpdateProductStream(ServerContext* context, ServerReader<product::UpdateRequest>* reader, product::QueryReply* response) override;


        Status CreateProductBidiStream(ServerContext* context, ServerReaderWriter<product::QueryReply, product::CreateRequest>* stream) override;
    private:
        bool on_changed(product_table_t previousState, product_table_t currentState);
    private:
        bool m_on_change;
        std::string m_string;
        std::atomic<bool> m_stream;
        product::ProductsReply m_reply;
        std::mutex m_mutex;
        std::condition_variable m_condition;
    };
}