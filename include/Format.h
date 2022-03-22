#pragma once

#include <cstdio>
#include <string>
#include <memory>

template<typename... Args>
__declspec(dllexport)
inline std::string Format(const std::string& format, Args... args)
{
	auto size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
	auto buffer = std::make_unique<char[]>(size);

	std::snprintf(buffer.get(), size, format.c_str(), args...);

	return std::string(buffer.get(), size - 1);
}