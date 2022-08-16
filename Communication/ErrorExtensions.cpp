#include "ErrorExtensions.h"

#include <memory>
#include <system_error>

std::wstring GetErrorMessage(const DWORD errorCode)
{
	LPTSTR message = nullptr;

	constexpr int flags = FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS
		| FORMAT_MESSAGE_ALLOCATE_BUFFER;

	const DWORD messageLength = FormatMessage(
		flags,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPTSTR>(&message),
		0,
		nullptr);

	if (messageLength <= 0)
	{
		const auto errorCode = GetLastError();

		throw std::system_error(
			errorCode,
			std::system_category(),
			"Failed to retrieve error message string.");
	}

	auto deleter = [](void* p) { LocalFree(p); };

	const auto ptrBuffer = std::unique_ptr<wchar_t, decltype(deleter)>(message, deleter);

	return { ptrBuffer.get(), messageLength };
}
