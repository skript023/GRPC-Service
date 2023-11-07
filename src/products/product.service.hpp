#pragma once
#include "common.hpp"
#include "service_invoker.hpp"
#include "entity/product.entity.hpp"

#include "protobuf/product.grpc.pb.h"

using namespace product;
using namespace grpc;

namespace microservice
{
    using product_table_t = std::vector<microservice::Products, std::allocator<microservice::Products>>; 
    using proto_table_t = google::protobuf::RepeatedPtrField<std::string>; 
    
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
        bool on_changed(product_table_t previousState, product_table_t currentState);
    private:
        bool m_on_change;
        std::string m_string;
        std::atomic<bool> m_stream;
        ProductsReply m_reply;
        std::mutex m_mutex;
        std::condition_variable m_condition;
    };
}