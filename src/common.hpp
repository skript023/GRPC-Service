#pragma once

#include <iostream>
#include <Windows.h>
#include <chrono>
#include <TlHelp32.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include <stack>
#include <regex>
#include <array>

#include "logger.hpp"
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#define SECRET "CPP GOTTVERGESSEN"
#define NODISCARD [[nodiscard]]
#define API "/api/v1"

namespace cms
{
	using namespace std::chrono_literals;
	inline std::atomic_bool g_running{ true };
}