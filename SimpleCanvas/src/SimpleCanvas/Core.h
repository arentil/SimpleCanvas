#pragma once

#ifdef SC_BUILD_DLL
	#define SC_API __declspec(dllexport)
#else
	#define SC_API __declspec(dllimport)
#endif

#ifdef ASSERTION_ENABLED
	#define SC_ASSERT(x, FAIL_STRING) { if(!(x)) { LOG_ERROR("Assertion failed!" + FAIL_STRING); __debugbreak(); } }
#else
	#define SC_ASSERT(x, ...)
#endif