#include "ChatHandler.h"

#include "Trace.h"

void ChatHandler::Handle(std::string message)
{
	Trace(message.c_str());
}
