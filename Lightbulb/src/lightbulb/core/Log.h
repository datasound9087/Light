#pragma once
#include <spdlog/spdlog.h>
class Log
{
public:
	static void init(const std::string& name);
	static std::shared_ptr<spdlog::logger>& getLogger() { return logger;  }

private:
	static std::shared_ptr<spdlog::logger> logger;
};

#ifdef CONFIG_DEBUG
	#define TRACE(...)    ::Log::getLogger()->trace(__VA_ARGS__)
	#define INFO(...)     ::Log::getLogger()->info(__VA_ARGS__)
	#define WARN(...)     ::Log::getLogger()->warn(__VA_ARGS__)
	#define ERROR(...)    ::Log::getLogger()->error(__VA_ARGS__)
	#define CRITICAL(...) ::Log::getLogger()->critical(__VA_ARGS__)
#else
	#define TRACE(...)   
	#define INFO(...)    
	#define WARN(...)    
	#define ERROR(...)   
	#define CRITICAL(...)
#endif

