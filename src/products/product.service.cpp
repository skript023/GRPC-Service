#include "product.service.hpp"
#include "streaming.hpp"
#include "database.hpp"

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply)
	{
		auto products = g_database->storage().get_all<Products>();
		if (products.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");;

		for (auto& product : products)
		{
			reply->mutable_products()->Add(std::move(product.name));
		}

		return Status::OK;
	}
	Status ProductService::FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply)
	{
		auto product = g_database->storage().get<Products>(request->id());
		if (product.name.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");

		reply->set_id(product.id);
		reply->set_name(product.name);

		return Status::OK;
	}
	Status ProductService::CreateProduct(ServerContext* context, const CreateRequest* request, QueryReply* reply)
	{
		if (request->name().empty())
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		Products product;
		product.id = -1;
		product.name = request->name();
		product.description = request->name();

		int data = g_database->storage().insert(product);

		reply->set_message(fmt::format("{} successfully created", data));
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply)
	{
		auto product = g_database->storage().get<Products>(request->id());

		if (product.name.empty())
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		product.name = request->name();
		product.description = request->name();

		g_database->storage().update(product);

		reply->set_message(fmt::format("{} successfully updated", product.name));
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::RemoveProduct(ServerContext* context, const FindByIdRequest* request, QueryReply* reply)
	{
		try
		{
			g_database->storage().remove<Products>(request->id());
		
			reply->set_message("data successfully deleted");
			reply->set_success(true);
		}
		catch(std::system_error e)
		{
			LOG(WARNING) << e.what();

			return Status::CANCELLED;
		}

		return Status::OK;
	}
	Status ProductService::FindAllProductStream(ServerContext* context, const EmptyRequest* request, ServerWriter<ProductsReply>* reply)
	{
		auto storage = g_database->storage();
		auto products = storage.get_all<Products>();
		
		if (products.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Unable to stream due to data not found");

		for (auto& product : products)
		{
			m_reply.mutable_products()->Add(std::move(product.name));
		}

		m_stream = reply->Write(m_reply);

		while (m_stream)
		{
			std::unique_lock lock(m_mutex);
			
			if (this->on_changed(products, storage.get_all<Products>()))
			{
				for (auto& product : products)
				{
					m_reply.mutable_products()->Add(std::move(product.name));
				}
				m_stream = reply->Write(m_reply);
			}
			if (!m_stream) break;
		}

		return Status::OK;
	}
	Status ProductService::UpdateProductStream(ServerContext* context, ServerReader<UpdateRequest>* reader, QueryReply* response)
	{
		auto storage = g_database->storage();
		UpdateRequest request;
		while (reader->Read(&request))
		{
			std::unique_lock lock(m_mutex);

			auto product = storage.get<Products>(request.id());
			product.name = request.name();
			product.description = request.name();

			storage.update(product);
			
			response->set_message(fmt::format("{} successfully updated", product.name));
			response->set_success(true);
		}
		return Status::OK;
	}
	Status ProductService::CreateProductBidiStream(ServerContext* context, ServerReaderWriter<QueryReply, CreateRequest>* stream)
	{
		CreateRequest request;
		QueryReply reply;
		Products product;
		
		while (stream->Read(&request))
		{
			std::unique_lock lock(m_mutex);
			
			product.id = -1;
			product.name = request.name();
			product.description = request.name();

			if (int data = g_database->storage().insert(product); data != 0)
			{
				reply.set_message(fmt::format("{} has successfully added", request.name()));
				reply.set_success(true);
				stream->Write(reply);
			}
		}

		return Status::OK;
	}
	bool ProductService::on_changed(product_table_t& previousState, product_table_t const& currentState)
	{
		if (currentState.size() > previousState.size())
		{
			previousState = currentState;
			return true;
		}

		if (previousState.size() > currentState.size())
		{
			previousState = currentState;
			return true;
		}

		for (size_t i = 0; i < previousState.size() || i < currentState.size(); i++)
		{
			LOG(INFO) << previousState[i].name << " - " << currentState[i].name;
			if (previousState[i].name != currentState[i].name)
			{
				previousState = currentState;

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