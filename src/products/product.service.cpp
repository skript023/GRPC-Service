#include "product.service.hpp"

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ServerWriter<ProductsReply>* reply)
	{
		size_t size = m_mock_data.size();
		ProductsReply replies; replies.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
		grpc::WriteOptions opt;
		while (reply->Write(replies))
		{
			if (size < m_mock_data.size())
			{
				break;
			}
			std::this_thread::sleep_for(1s);
		}

		replies.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
		reply->WriteLast(replies, opt.set_last_message());

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

		auto data = m_mock_data.emplace_back(std::move(request->name()));
		reply->set_message(fmt::format("{} successfully created", data));
		ProductsReply replies; replies.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());

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
}