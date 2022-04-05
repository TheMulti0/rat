#pragma once

#include <cstdarg>
#include <cstdio>
#include <mutex>

__declspec(dllexport)
inline void Trace(const char* format, ...)
{
	static std::mutex mutex;
	std::lock_guard guard(mutex);

	va_list arguments;
	va_start(arguments, format);

	vprintf(format, arguments);

	va_end(arguments);
}
