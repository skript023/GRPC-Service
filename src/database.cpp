#include "database.hpp"

namespace microservice
{
    database::database()
    {
        auto storage = this->storage();
        storage.sync_schema();

        g_database = this;
    }

    database::~database()
    {
        g_database = nullptr;
    }
} // namespace microservice
