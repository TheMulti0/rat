#pragma once

#include <cstdarg>
#include <cstdio>
#include <mutex>

inline void Trace(const char* format, ...)
{
	static std::mutex _mutex;
	std::lock_guard<std::mutex> guard(_mutex);

	va_list arguments;
	va_start(arguments, format);

	vprintf(format, arguments);

	va_end(arguments);
}
