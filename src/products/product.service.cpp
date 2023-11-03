#include "product.service.hpp"

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply)
	{
		reply->mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());

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
	Status ProductService::CreateProduct(ServerContext* context, const CreateRequest* request, ProductReply* reply)
	{
		if (request->name().empty())
			return Status::CANCELLED;

		reply->set_id(m_mock_data.size() + 1);
		auto data = m_mock_data.emplace_back(std::move(request->name()));
		reply->set_name(data);

		return Status::OK;
	}
	Status ProductService::UpdateProduct(ServerContext* context, const UpdateRequest* request, ProductReply* reply)
	{
		m_mock_data[request->id()] = request->name();
		reply->set_id(request->id());
		reply->set_name(request->name());

		return Status::OK;
	}
	Status ProductService::RemoveProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply)
	{
		m_mock_data.erase(m_mock_data.begin() + request->id());
		reply->set_name(m_mock_data[request->id()]);

		return Status::OK;
	}
}