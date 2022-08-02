#pragma once

#include <stdexcept>
#include <string>
#include <memory>
#include <Windows.h>

#include "StringExtensions.h"

__declspec(dllexport)
std::wstring GetErrorMessage(DWORD errorCode);

template<typename... Args>
__declspec(dllexport)
void ThrowRuntimeException(const std::string& format, Args... args)
{
	auto size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
	auto buffer = std::make_unique<char[]>(size);

	std::snprintf(buffer.get(), size, format.c_str(), args...);

	const auto message = std::string(buffer.get(), size - 1);

	throw std::runtime_error(message);
}

template<typename... Args>
__declspec(dllexport)
void ThrowWinApiException(const std::string& format, Args... args)
{
	DWORD lastError = GetLastError();
	const std::string lastErrorMessage = ToString(GetErrorMessage(lastError));

	const auto errorMessageFormat = "Failed with error code %d: %s";

	ThrowRuntimeException(
		format + "\n" + errorMessageFormat,
		args...,
		lastError,
		lastErrorMessage.c_str());
}