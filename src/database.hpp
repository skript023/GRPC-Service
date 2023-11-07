#pragma once
#include "common.hpp"

#include "products/entity/product.entity.hpp"
#include "activities/entity/activities.entity.hpp"

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
            auto products = make_table("products", 
            make_column("id", &Products::id, autoincrement(), primary_key()), 
            make_column("name", &Products::name), 
            make_column("description", &Products::description));

            auto activities = make_table("activities", 
            make_column("id", &Activity::id, autoincrement(), primary_key()), 
            make_column("name", &Activity::name), 
            make_column("start_date", &Activity::start_date),
            make_column("end_date", &Activity::end_date));

        
            return make_storage("grpc.sqlite", products, activities);
        }
    };

    inline database* g_database;
}