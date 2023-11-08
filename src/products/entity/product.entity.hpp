#pragma once

#include <sqlite_orm/sqlite_orm.h>

namespace microservice
{
    struct Products
    {
        int id;
        int price;
        std::string name;
        std::string description;
    };
    
} // namespace microservice
