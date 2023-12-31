#pragma once
#include "common.hpp"

#include "protobuf/activity.grpc.pb.h"
#include "entity/activities.entity.hpp"

using namespace grpc;

namespace microservice
{
    class ActivityService final : public activity::Activity::Service
    {
        Status FindAllActivity(ServerContext* context, const activity::EmptyRequest* request, activity::ActivitiesReply* response) override;
        Status FindOneActivity(ServerContext* context, const activity::FindByIdRequest* request, activity::ActivityReply* response) override;
        Status CreateActivity(ServerContext* context, const activity::CreateRequest* request, activity::QueryReply* response) override;
        Status UpdateActivity(ServerContext* context, const activity::UpdateRequest* request, activity::QueryReply* response) override;
        Status RemoveActivity(ServerContext* context, const activity::FindByIdRequest* request, activity::QueryReply* response) override;
        Status FindAllActivityStream(ServerContext* context, const activity::EmptyRequest* request, ServerWriter< activity::ActivitiesReply>* writer) override;
        Status FindOneActivityStream(ServerContext* context, const activity::FindByIdRequest* request, ServerWriter< activity::ActivityReply>* writer) override;
        Status UpdateActivityBidiStream(ServerContext* context, ServerReaderWriter<activity::QueryReply, activity::UpdateRequest> *stream) override;
        Status CreateActivityBidiStream(ServerContext* context, ServerReaderWriter<activity::QueryReply, activity::CreateRequest>* stream) override;
        Status RemoveActivityBidiStream(ServerContext* context, ServerReaderWriter<activity::QueryReply, activity::FindByIdRequest>* stream);
    private:
        activity::ActivityReply m_reply;
        activity::ActivitiesReply m_replies;
    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;
        bool m_stream;
        bool m_on_change = false;
    };
}
