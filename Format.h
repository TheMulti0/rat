#pragma once

#include <cstdarg>
#include <cstdio>
#include <string>
#include <memory>

template<typename... Args>
inline std::string Format(const std::string& format, Args... args)
{
	const auto size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
	const auto buffer = std::make_unique<char[]>(size);

	std::snprintf(buffer.get(), size, format.c_str(), args...);

	return std::string(buffer.get(), buffer.get() + size - 1);
}