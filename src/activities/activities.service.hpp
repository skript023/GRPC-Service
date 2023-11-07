#pragma once
#include "common.hpp"

#include "protobuf/activity.grpc.pb.h"

using namespace activity;
using namespace grpc;

namespace microservice
{
    class ActivityService final : public Activity::Service
    {
        Status FindAllProduct(ServerContext* context, const EmptyRequest* request, ActivitiesReply* response) override;
        Status FindOneProduct(ServerContext* context, const FindByIdRequest* request, ActivityReply* response);
        Status CreateProduct(ServerContext* context, const CreateRequest* request, QueryReply* response);
        Status UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* response);
        Status RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* response);
        Status QueryProduct(ServerContext* context, ServerReaderWriter< ActivityReply, PaginationRequest>* stream);
        Status FindAllProductStream(ServerContext* context, const EmptyRequest* request, ServerWriter< ActivitiesReply>* writer);
        Status UpdateProductStream(ServerContext* context, ServerReader< UpdateRequest>* reader, QueryReply* response);
        Status CreateProductBidiStream(ServerContext* context, ServerReaderWriter< QueryReply, CreateRequest>* stream);
    };
}
