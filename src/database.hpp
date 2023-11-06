#pragma once
#include "common.hpp"

namespace microservice
{
    using namespace sqlite_orm;

	class database
    {
    public:
        explicit database();
        ~database() noexcept = default;
    };
}