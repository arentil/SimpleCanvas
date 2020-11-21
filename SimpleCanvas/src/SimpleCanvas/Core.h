#pragma once

#ifdef SC_BUILD_DLL
	#define SC_API __declspec(dllexport)
#else
	#define SC_API __declspec(dllimport)
#endif

#ifdef SC_ASSERT_ENABLED
	#define SC_ASSERT(x, text) { if(!(x)) { LOG_ERROR(text); __debugbreak(); } }
#else
	#define SC_ASSERT(x, ...)
#endif