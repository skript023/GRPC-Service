#include "product.service.hpp"
#include "streaming.hpp"
#include "database.hpp"

using namespace product;

namespace microservice
{
	Status ProductService::FindAllProduct(ServerContext* context, const EmptyRequest* request, ProductsReply* reply)
	{
		auto products = g_database->storage().get_all<Products>();
		if (products.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");;

		std::ranges::for_each(products, [=](Products product)
		{
			m_reply.set_id(product.id);
            m_reply.set_price(product.price);
            m_reply.set_name(product.name);
            m_reply.set_description(product.description);

			reply->mutable_products()->Add(std::move(m_reply));
		});

		return Status::OK;
	}
	Status ProductService::FindOneProduct(ServerContext* context, const FindByIdRequest* request, ProductReply* reply)
	{
		auto product = g_database->storage().get<Products>(request->id());
		if (product.name.empty())
			return Status(static_cast<grpc::StatusCode>(GRPC_STATUS_NOT_FOUND), "Data not found");

		reply->set_id(product.id);
		reply->set_price(product.price);
		reply->set_name(product.name);
		reply->set_description(product.description);

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
		product.price = request->price();
		product.name = request->name();
		product.description = request->description();

		int data = g_database->storage().insert(product);

		reply->set_message(fmt::format("{} successfully created", data));
		reply->set_success(true);

		return Status::OK;
	}
	Status ProductService::UpdateProduct(ServerContext* context, const UpdateRequest* request, QueryReply* reply)
	{
		auto storage = g_database->storage(); 
		auto product = g_database->storage().get_pointer<Products>(request->id());

		if (!product)
		{
			reply->set_message("Unable to create empty data");

			return Status::CANCELLED;
		}

		product->price = request->price();
		product->name = request->name();
		product->description = request->description();

		storage.update(*product);

		reply->set_message(fmt::format("{} successfully updated", product->name));
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

		std::ranges::for_each(products, [this](Products product)
		{
			m_reply.set_id(product.id);
            m_reply.set_price(product.price);
            m_reply.set_name(product.name);
            m_reply.set_description(product.description);

			m_replies.mutable_products()->Add(std::move(m_reply));
		});

		m_stream = reply->Write(m_replies);

		while (m_stream)
		{
			if (this->on_changed(products, storage.get_all<Products>()))
			{
				products = storage.get_all<Products>();
				m_replies.clear_products();
				std::ranges::for_each(products, [this](Products product)
				{
					m_reply.set_id(product.id);
					m_reply.set_price(product.price);
					m_reply.set_name(product.name);
					m_reply.set_description(product.description);

					m_replies.mutable_products()->Add(std::move(m_reply));
				});
				
				m_stream = reply->Write(m_replies);
			}
			if (!m_stream) break;

			std::this_thread::sleep_for(1s);
		}

		return Status::OK;
	}
	Status ProductService::UpdateProductStream(ServerContext* context, ServerReader<UpdateRequest>* reader, QueryReply* response)
	{
		auto storage = g_database->storage();
		UpdateRequest request;
		while (reader->Read(&request))
		{
			{
				std::unique_lock lock(m_mutex);

				m_condition.wait(lock, [request] {return &request;});
				
				auto product = storage.get<Products>(request.id());
				product.price = request.price();
				product.name = request.name();
				product.description = request.description();

				storage.update(product);

				lock.unlock();
			}
		}
		return Status::OK;
	}
	Status ProductService::CreateProductBidiStream(ServerContext* context, ServerReaderWriter<QueryReply, CreateRequest>* stream)
	{
		auto storage = g_database->storage();
		CreateRequest request;
		QueryReply reply;
		Products product;
		
		while (stream->Read(&request))
		{
			{
				std::unique_lock lock(m_mutex);

				m_condition.wait(lock, [request] {return &request;});
			
				product.id = -1;
				product.price = request.price();
				product.name = request.name();
				product.description = request.description();

				if (int data = storage.insert(product); data != 0)
				{
					reply.set_message(fmt::format("{} has successfully added", request.name()));
					reply.set_success(true);
					stream->Write(reply);
				}
				else
				{
					reply.set_message(fmt::format("{} has failed added", request.name()));
					reply.set_success(false);
					stream->Write(reply);
				}

				lock.unlock();
			}
		}

		return Status::OK;
	}
	bool ProductService::on_changed(product_table_t previousState, product_table_t currentState)
	{
		if (currentState.size() > previousState.size())
		{
			previousState = g_database->storage().get_all<Products>();
			return true;
		}

		if (previousState.size() > currentState.size())
		{
			return true;
		}

		for (size_t i = 0; i < previousState.size() || i < currentState.size(); i++)
		{
			if (previousState[i].name != currentState[i].name)
			{
				return true;
			}
		}

		return false;
	}
}