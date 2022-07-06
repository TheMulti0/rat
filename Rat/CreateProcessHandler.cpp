#include <string>

#include "CreateProcessHandler.h"

#include "Process.h"

void CreateProcessHandler::Handle(std::span<char> content)
{
	const auto message = std::wstring(content.begin(), content.end());

	auto p = Process(message, false, true);
}