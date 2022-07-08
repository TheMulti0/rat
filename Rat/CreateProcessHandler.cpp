#include <string>

#include "CreateProcessHandler.h"

#include "Process.h"

void CreateProcessHandler::Handle(MessageType type, std::span<char> content)
{
	const auto message = std::wstring(content.begin(), content.end());

	auto p = Process(message, false, true);
}