#include "ChatHandler.h"

#include "Trace.h"

void ChatHandler::Handle(std::span<char> content)
{
	const auto message = std::string(content.begin(), content.end());
	Trace("Received %s\n", message.c_str());
}
