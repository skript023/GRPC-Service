#include "activities.service.hpp"
#include "database.hpp"

using namespace activity;

namespace microservice
{
    Status ActivityService::FindAllActivity(ServerContext *context, const EmptyRequest *request, ActivitiesReply *response)
    {
        auto activities = g_database->storage().get_all<Activities>();

		if (activities.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");;

		std::ranges::for_each(activities, [=](Activities activity)
        {
            m_reply.set_id(activity.id);
            m_reply.set_name(activity.name);
            m_reply.set_start_date(activity.start_date);
            m_reply.set_end_date(activity.end_date);
            m_reply.set_status(activity.status);

            response->mutable_activities()->Add(std::move(m_reply));
        });

        return Status::OK;
    }
    Status ActivityService::FindOneActivity(ServerContext *context, const FindByIdRequest *request, ActivityReply *response)
    {
        auto activity = g_database->storage().get_pointer<Activities>(request->id());
		if (!activity)
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");

		response->set_id(activity->id);
		response->set_name(activity->name);
		response->set_start_date(activity->start_date);
		response->set_end_date(activity->end_date);
		response->set_status(activity->status);

		return Status::OK;
    }
    Status ActivityService::CreateActivity(ServerContext *context, const CreateRequest *request, QueryReply *response)
    {
        if (!request)
		{
			response->set_message("Request cannot be empty");

			return Status::CANCELLED;
		}

		Activities activity;
		activity.id = -1;
		activity.name = request->name();
		activity.start_date = request->start_date();
		activity.end_date = request->end_date();
        activity.status = request->status();

		if (int data = g_database->storage().insert(activity); data == 0)
        {
            response->set_message(fmt::format("{} failed created", activity.name));
        }

		response->set_message(fmt::format("{} successfully created", activity.name));
		response->set_success(true);

		return Status::OK;
    }
    Status ActivityService::UpdateActivity(ServerContext *context, const UpdateRequest *request, QueryReply *response)
    {
        auto storage = g_database->storage(); 
		auto activity = g_database->storage().get_pointer<Activities>(request->id());

		if (!activity)
		{
			response->set_message("Request cannot be empty");

			return Status::CANCELLED;
		}

		activity->name = request->name();
		activity->start_date = request->start_date();
		activity->end_date = request->end_date();
		activity->status = request->status();

		storage.update(*activity);

		response->set_message(fmt::format("{} successfully updated", activity->name));
		response->set_success(true);

		return Status::OK;
    }
    Status ActivityService::RemoveActivity(ServerContext *context, const FindByIdRequest *request, QueryReply *response)
    {
        try
		{
			g_database->storage().remove<Activities>(request->id());
		
			response->set_message("data successfully deleted");
			response->set_success(true);
		}
		catch(std::system_error e)
		{
			LOG(WARNING) << e.what();

			return Status::CANCELLED;
		}

		return Status::OK;
    }
    Status ActivityService::FindAllActivityStream(ServerContext *context, const EmptyRequest *request, ServerWriter<ActivitiesReply> *writer)
    {
        auto storage = g_database->storage();
		auto activities = storage.get_all<Activities>();
		
		
		if (activities.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Unable to stream due to data not found");

		std::ranges::for_each(activities, [this](Activities activity)
		{
			m_reply.set_id(activity.id);
            m_reply.set_name(activity.name);
            m_reply.set_start_date(activity.start_date);
            m_reply.set_end_date(activity.end_date);
            m_reply.set_status(activity.status);

			m_replies.mutable_activities()->Add(std::move(m_reply));
		});

		while (writer->Write(m_replies))
		{
			{
				std::unique_lock lock(m_mutex);

				m_condition.wait(lock, [this] { return m_on_change; });

				activities = storage.get_all<Activities>();
				m_replies.clear_activities();
				std::ranges::for_each(activities, [this](Activities activity)
				{
					m_reply.set_id(activity.id);
                    m_reply.set_name(activity.name);
                    m_reply.set_start_date(activity.start_date);
                    m_reply.set_end_date(activity.end_date);
                    m_reply.set_status(activity.status);

                    m_replies.mutable_activities()->Add(std::move(m_reply));
				});
				
				m_on_change = false;

				lock.unlock();
			}
		}

		return Status::OK;
    }
    Status ActivityService::UpdateActivityStream(ServerContext *context, ServerReader<UpdateRequest> *reader, QueryReply *response)
    {
        auto storage = g_database->storage();
		UpdateRequest request;

		while (reader->Read(&request))
		{
			{
				std::unique_lock lock(m_mutex);

				m_condition.wait(lock, [request] { return &request; });
				
				auto activity = storage.get_pointer<Activities>(request.id());

                if (!activity)
                {
                    return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Unable to update data, not found");
                }

				activity->name = request.name();
				activity->start_date = request.start_date();
				activity->end_date = request.end_date();
				activity->status = request.status();

				storage.update(*activity);
				m_on_change = true;

				lock.unlock();
			}

			m_condition.notify_one();
		}
		return Status::OK;
    }
    Status ActivityService::CreateActivityBidiStream(ServerContext *context, ServerReaderWriter<QueryReply, CreateRequest> *stream)
    {
        auto storage = g_database->storage();
		CreateRequest request;
		QueryReply reply;
		Activities activity;
		
		while (stream->Read(&request))
		{
			{
				std::unique_lock lock(m_mutex);

				m_condition.wait(lock, [request] { return &request; });
			
				activity.id = -1;
				activity.name = request.name();
				activity.start_date = request.start_date();
				activity.end_date = request.end_date();
				activity.status = request.status();

				if (int data = storage.insert(activity); data != 0)
				{
					reply.set_message(fmt::format("{} has successfully added", request.name()));
					reply.set_success(true);
					stream->Write(reply);
					m_on_change = true;
				}
				else
				{
					reply.set_message(fmt::format("{} has failed added", request.name()));
					reply.set_success(false);
					stream->Write(reply);
				}

				lock.unlock();
			}

			m_condition.notify_one();
		}

		return Status::OK;
    }
    Status ActivityService::QueryActivity(ServerContext *context, ServerReaderWriter<ActivityReply, PaginationRequest> *stream)
    {
        return Status();
    }
}