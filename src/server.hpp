#pragma once
#include "common.hpp"
#include "greeter/greeter.service.hpp"
#include "products/product.service.hpp"

namespace microservice
{
    class server final 
    {
    public:
        ~server() noexcept;

        // There is no shutdown handling in this code.
        void run(uint16_t port);
    private:
        GreeterService m_greeter_service;
        ProductService m_product_service;
        std::unique_ptr<Server> m_server;
    };
}