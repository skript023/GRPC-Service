#include "server.hpp"

namespace microservice
{
    server::~server() noexcept
    {
        m_server->Shutdown();
    }

	void server::run(uint16_t port)
	{
        std::string server_address = absl::StrFormat("0.0.0.0:%d", port);

        grpc::EnableDefaultHealthCheckService(true);
        grpc::reflection::InitProtoReflectionServerBuilderPlugin();
        ServerBuilder builder;
        // Listen on the given address without any authentication mechanism.
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        // Register "service" as the instance through which we'll communicate with
        // clients. In this case it corresponds to an *synchronous* service.
        builder.RegisterService(&m_greeter_service);
        builder.RegisterService(&m_product_service);
        builder.RegisterService(&m_activity_service);
        // Finally assemble the server.
        m_server = builder.BuildAndStart();
        LOG(INFO) << "Server listening on " << server_address;

        // Wait for the server to shutdown. Note that some other thread must be
        // responsible for shutting down the server for this call to ever return.
        m_server->Wait();
	}
}