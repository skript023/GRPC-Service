#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <stack>
#include <regex>
#include <array>
#include <chrono>
#include <fstream>
#include <optional>
#include <exception>
#include <functional>
#include <filesystem>
#include <algorithm>
#include <cstdio>
#include <cstdint>

#ifdef __linux__

#elif _WIN32
#include <Windows.h>
#endif

#include "fmt/format.h"

#include "logger.hpp"

// GRPC Dependencies Begin
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
// GRPC Dependencies End

#define NODISCARD [[nodiscard]]

namespace microservice
{
	using namespace std::chrono_literals;
	inline std::atomic_bool g_running{ true };
}