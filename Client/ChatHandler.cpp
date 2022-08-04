#include "ChatHandler.h"

#include "Trace.h"

void ChatHandler::Handle(MessageType type, SharedSpan content)
{
	const auto message = content.String();

	Trace("Received %s\n", message.c_str());
}
