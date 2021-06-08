#pragma once

#ifdef SC_ASSERT_ENABLED
	#ifdef _WIN32
		#define SC_ASSERT(x, text, ...)   if(!(x)) { LOG_ERROR(text, ##__VA_ARGS__); __debugbreak(); }
	#else
		#define SC_ASSERT(x, text, ...)   if(!(x)) { LOG_ERROR(text, ##__VA_ARGS__); __builtin_trap(); }
	#endif
#else
	#define SC_ASSERT(x, ...)
#endif

#define GLFW_INCLUDE_NONE

#ifndef NDEBUG
	#define BUILD_TYPE_DEBUG
#else
	#define BUILD_TYPE_RELEASE
#endif