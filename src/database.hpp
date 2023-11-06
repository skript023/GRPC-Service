#pragma once
#include "common.hpp"

#include "products/entity/product.entity.hpp"

namespace microservice
{
    using namespace sqlite_orm;

	class database
    {
    public:
        explicit database();
        ~database() noexcept;

        auto storage()
        {
            const auto products = make_table("products", 
            make_column("id", &Products::id, autoincrement(), primary_key()), 
            make_column("name", &Products::name), 
            make_column("description", &Products::description));

        
            return make_storage("grpc.sqlite", products);
        }
    };

    inline database* g_database;
}