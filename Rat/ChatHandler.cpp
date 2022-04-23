#include "ChatHandler.h"

#include "Trace.h"

void ChatHandler::Handle(std::span<char> content)
{
	Trace(content.data());
}
