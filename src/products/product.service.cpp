#include "product.service.hpp"

namespace microservice
{
    using product::Product;

    using product::ProductReply;
    using product::QueryReply;
    using product::ProductsReply;

    using product::FindByIdRequest;
    using product::EmptyRequest;
    using product::UpdateRequest;
    using product::CreateRequest;
    using product::ProductsReply;
    using grpc::ServerAsyncWriter;

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
            m_status = PROCESS;

            this->find_all_begin();
        }
        else if (m_status == PROCESS)
        {
            this->find_all_end();
        }
        else
        {
            GPR_ASSERT(m_status == FINISH);
            // Once in the FINISH state, deallocate ourselves (register_service).
            delete this;
        }
    }
    product_service* product_service::find_all_begin()
    {
        m_service->RequestFindAllProductServerStream(&m_context, &m_request, &m_responder, m_completed_queue, m_completed_queue, this);

        return this;
    }
    product_service* product_service::find_all_end()
    {
        new product_service(m_service, m_completed_queue);
        this->populate_data();
        m_reply.mutable_products()->Assign(m_mock_data.begin(), m_mock_data.end());
        new product_service(m_service, m_completed_queue);

        m_responder.Write(m_reply, this);
        m_status = FINISH;

        return this;
    }
}