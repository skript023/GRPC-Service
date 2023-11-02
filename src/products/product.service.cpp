#include "product.service.hpp"

namespace microservice
{
    product_service::product_service(Product::AsyncService* service, ServerCompletionQueue* cq) :
        m_service(service), m_completed_queue(cq), m_responder(&m_context), m_status(CREATE)
    {
        // Invoke the serving logic right away.
        this->proceed();
    }
    void product_service::proceed()
    {
        if (m_status == CREATE)
        {
            // Make this instance progress to the PROCESS state.
            m_status = PROCESS;

            // As part of the initial CREATE state, we *request* that the system
            // start processing SayHello requests. In this request, "this" acts are
            // the tag uniquely identifying the request (so that different register_service
            // instances can serve different requests concurrently), in this case
            // the memory address of this register_service instance.
            m_service->RequestFindOneProduct(&m_context, &m_request, &m_responder, m_completed_queue, m_completed_queue, this);
        }
        else if (m_status == PROCESS)
        {
            // Spawn a new register_service instance to serve new clients while we process
            // the one for this register_service. The instance will deallocate itself as
            // part of its FINISH state.
            new product_service(m_service, m_completed_queue);

            // The actual processing.
            std::vector<std::string> data = { "Product A", "Product B"};
            std::string prefix("Hello ");
            m_reply.set_id(m_request.id());
            m_reply.set_name(data[m_request.id()]);

            // And we are done! Let the gRPC runtime know we've finished, using the
            // memory address of this instance as the uniquely identifying tag for
            // the event.
            m_status = FINISH;
            m_responder.Finish(m_reply, Status::OK, this);
        }
        else
        {
            GPR_ASSERT(m_status == FINISH);
            // Once in the FINISH state, deallocate ourselves (register_service).
            delete this;
        }
    }
}