#include "lbpch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::logger;

void Log::init(const std::string& name)
{
	spdlog::stdout_color_mt(name);
	logger = spdlog::get(name);
	logger->set_level(spdlog::level::trace);
	logger->set_pattern("%^[%T] %n: %v%$");
}
