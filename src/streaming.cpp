#include "streaming.hpp"

namespace microservice
{
	streaming::streaming(): m_locked(true)
	{
		g_streaming = this;
	}
	streaming::~streaming()
	{
		g_streaming = nullptr;
	}
	void streaming::next(callback_t func)
	{
		if (func)
		{
			m_locked = false;
			std::unique_lock lock(m_mutex);
			m_next_jobs.push(std::move(func));
			m_condition.wait(lock, [this]() { return !m_locked; });
			lock.unlock();
		}
	}
	void streaming::listen_stream()
	{
		m_locked = true;
		std::unique_lock lock(m_mutex);

		m_condition.wait(lock, [this]() { return !m_locked; });

		lock.unlock();

		m_condition.notify_all();
	}
	void streaming::end_stream()
	{
		m_locked = false;
		std::unique_lock lock(m_mutex);
		m_condition.wait(lock, [this]() { return !m_locked; });
		lock.unlock();
	}
	void streaming::listener()
	{
		for (;;)
		{
			std::unique_lock lock(m_mutex);
			if (!m_next_jobs.empty())
			{
				m_locked = true;
				auto job = std::move(m_next_jobs.top());
				m_next_jobs.pop();
				lock.unlock();

				std::invoke(std::move(job));
			}
		}
	}
}