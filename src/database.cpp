#include "database.hpp"

#include "products/entity/product.entity.hpp"

namespace microservice
{
    database::database()
    {
        const auto products = make_table("products", 
            make_column("id", &Products::id, autoincrement(), primary_key()), 
            make_column("first_name", &Products::name), 
            make_column("last_name", &Products::description));

        
        auto storage = make_storage("grpc.sqlite",products);
    }

} // namespace microservice
