#pragma once

#if CONFIG_DEBUG
	#if defined(PLATFORM_WINDOWS)
		#define DEBUGBREAK() __debugbreak()
	#elif defined(PLATFORM_LINUX)
		#include <signal.h>
		#define HZ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	
	#define ENABLE_ASSERTS
#else
	#define DEBUGBREAK()
#endif

#ifdef ENABLE_ASSERTS
	#include "Log.h"
	#define ASSERT(x, ...) { if(!(x)) {ERROR("Assert failed: {0}", __VA_ARGS__); DEBUGBREAK(); }}
#else
	#define ASSERT(x, ...)
#endif
