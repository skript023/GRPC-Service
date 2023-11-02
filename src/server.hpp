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
        std::unique_ptr<ServerCompletionQueue> m_completed_queue;
        Greeter::AsyncService m_greeter_service;
        Product::AsyncService m_product_service;
        std::unique_ptr<Server> m_server;
    private:
        // This can be run in multiple threads if needed.
        void handle();
    };
}