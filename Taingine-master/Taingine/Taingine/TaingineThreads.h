#pragma once
#include <thread>
#include <unordered_map>

namespace TaingineThreads {
	extern std::unordered_map<std::string, std::thread*> taingineThreads;
}