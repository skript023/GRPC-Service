#include "server.hpp"

namespace microservice
{
    server::~server() noexcept
    {
        m_server->Shutdown();
        // Always shutdown the completion queue after the server.
        m_completed_queue->Shutdown();
    }
    void server::run(uint16_t port)
    {
        std::string server_address = absl::StrFormat("0.0.0.0:%d", port);

        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "m_service" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *asynchronous* service.
        builder.RegisterService(&m_greeter_service);
        builder.RegisterService(&m_product_service);
        builder.RegisterService(&m_user_service);
        // Get hold of the completion queue used for the asynchronous communication
        // with the gRPC runtime.
        m_completed_queue = builder.AddCompletionQueue();
        // Finally assemble the server.
        m_server = builder.BuildAndStart();

        if (!m_server)
        {
            LOG(WARNING) << "Failed to start server.";
            return;
        }

        LOG(INFO) << "Server listening on " << server_address;

        // Proceed to the server's main loop.
        this->handle();
    }
    void server::handle()
    {
        // Spawn a new register_service instance to serve new clients.
        new greeter_service(&m_greeter_service, m_completed_queue.get());
        new product_service(&m_product_service, m_completed_queue.get());
        new user_service(&m_user_service, m_completed_queue.get());

        LOG(INFO) << "All service initialized.";

        void* tag;  // uniquely identifies a request.
        bool ok;
        while (true)
        {
            // Block waiting to read the next event from the completion queue. The
            // event is uniquely identified by its tag, which in this case is the
            // memory address of a register_service instance.
            // The return value of Next should always be checked. This return value
            // tells us whether there is any kind of event or m_completed_queue is shutting down.
            GPR_ASSERT(m_completed_queue->Next(&tag, &ok));
            GPR_ASSERT(ok);
            static_cast<service_invoker*>(tag)->proceed();
        }
    }
}