#include "product.service.hpp"
#include "streaming.hpp"

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply)
	{
		if (m_mock_data.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");;

		m_reply.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());

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
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		auto data = m_mock_data.emplace_back(request->name());

		reply->set_message(fmt::format("{} successfully created", data));
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply)
	{
		if (request->name().empty() || request->id() > m_mock_data.size())
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		auto result = m_mock_data[request->id()] = request->name();
		reply->set_message(fmt::format("{} successfully updated", result));
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* reply)
	{
		if (m_mock_data[request->id()].empty() || m_mock_data.empty())
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		m_mock_data.erase(m_mock_data.begin() + request->id());

		reply->set_message("data successfully deleted");
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::FindAllProductStream(ServerContext* context, const EmptyRequest* request, ServerWriter<ProductsReply>* reply)
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
			std::unique_lock<std::mutex> lock(m_mutex);
			if (this->on_changed(data))
			{
				m_reply.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
				reply->Write(m_reply);
			}
			if (!m_stream) break;
		}

		return Status::OK;
	}
	Status ProductService::CreateProductBidiStream(ServerContext* context, ServerReaderWriter<QueryReply, CreateRequest>* stream)
	{
		CreateRequest data;
		QueryReply reply;
		while (stream->Read(&data))
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			
			if (this->does_exist(data.name()))
			{
				reply.set_message(fmt::format("{} is already exist", data.name()));
				stream->Write(reply);
			}
			else
			{
				if (!m_mock_data.emplace_back(data.name()).empty())
				{
					reply.set_message(fmt::format("{} has successfully added", data.name()));
					reply.set_success(true);
					stream->Write(reply);
				}
			}
		}

		return Status::OK;
	}
	bool ProductService::on_changed(std::vector<std::string>& previousState)
	{
		if (m_mock_data.size() > previousState.size())
		{
			previousState = m_mock_data;
			return true;
		}

		if (previousState.size() > m_mock_data.size())
		{
			previousState = m_mock_data;
			return true;
		}

		for (size_t i = 0; i < previousState.size() || i < m_mock_data.size(); i++)
		{
			if (previousState[i] != m_mock_data[i])
			{
				// Element was updated
				std::cout << "Element '" << previousState[i] << "' at index " << i << " was updated to '" << m_mock_data[i] << "'" << std::endl;
				previousState = m_mock_data;
				return true;
			}
		}

		return false;
	}
	bool ProductService::does_exist(std::string const& element)
	{
		for (auto& value : m_mock_data) 
		{
			if (value == element) 
			{
				return true;
			}
		}
		return false;
	}
}