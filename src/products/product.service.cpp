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
		if (m_mock_data[request->id()].empty())
			return Status::CANCELLED;

		reply->set_id(request->id());
		reply->set_name(m_mock_data[request->id()]);

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