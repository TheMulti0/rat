#include "ChatHandler.h"

#include "Trace.h"

bool ChatHandler::CanHandle(const MessageType type)
{
	return type == MessageType::Chat;
}

void ChatHandler::Handle(MessageType type, SharedSpan content)
{
	const auto message = content.String();

	Trace("Received %s\n", message.c_str());
}
