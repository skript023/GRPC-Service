#include "product.service.hpp"
#include "streaming.hpp"

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ServerWriter<ProductsReply>* reply)
	{
		if (m_mock_data.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");;

		size_t size = m_mock_data.size();
		auto data = m_mock_data;
		m_reply.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
		grpc::WriteOptions opt;

		reply->Write(m_reply);

		while (m_stream)
		{
			if (this->on_changed(data))
			{
				data = m_mock_data;
				m_reply.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
				reply->Write(m_reply);
			}
			if (!m_stream) break;

			std::this_thread::sleep_for(1s);
		}

		return Status::OK;
	}
	Status ProductService::FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply)
	{
		if (request->id() >= m_mock_data.size())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");

		reply->set_id(request->id());
		reply->set_name(m_mock_data[request->id()]);

		return Status::OK;
	}
	Status ProductService::CreateProduct(ServerContext* context, const CreateRequest* request, QueryReply* reply)
	{
		if (request->name().empty())
			return Status::CANCELLED;

		auto data = m_mock_data.emplace_back(request->name());
		reply->set_message(fmt::format("{} successfully created", data));

		return Status::OK;
	}
	Status ProductService::UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply)
	{
		auto result = m_mock_data[request->id()] = request->name();
		reply->set_message(fmt::format("{} successfully updated", result));

		return Status::OK;
	}
	Status ProductService::RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* reply)
	{
		m_mock_data.erase(m_mock_data.begin() + request->id());
		
		reply->set_message("data successfully deleted");

		return Status::OK;
	}
	bool ProductService::on_changed(const std::vector<std::string>& previousState)
	{
		if (m_mock_data.size() > previousState.size())
		{
			// Element was added to the end of the current vector
			return true;
		}

		if (previousState.size() > m_mock_data.size())
		{
			// Element was removed from the end of the current vector
			return true;
		}

		for (size_t i = 0; i < previousState.size() || i < m_mock_data.size(); i++)
		{
			if (previousState[i] != m_mock_data[i])
			{
				// Element was updated
				std::cout << "Element '" << previousState[i] << "' at index " << i << " was updated to '" << m_mock_data[i] << "'" << std::endl;
				return true;
			}
		}

		return false;
	}
}