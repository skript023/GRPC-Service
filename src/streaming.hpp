#pragma once

namespace microservice
{
	using callback_t = std::function<void()>;

	class streaming
	{
		bool m_locked;
		std::mutex m_mutex;
		std::stack<callback_t> m_next_jobs;
		std::condition_variable m_condition;
	public:
		explicit streaming();
		~streaming();
		void next(callback_t func);
		void listen_stream();
		void end_stream();
		void listener();
	};

	inline streaming* g_streaming;
}