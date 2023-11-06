#pragma once

#include <sqlite_orm/sqlite_orm.h>

namespace microservice
{
    struct Products
    {
        int id;
        std::string name;
        std::string description;
    };
    
} // namespace microservice
