#include "PingHandler.h"

bool PingHandler::CanHandle(MessageType type)
{
	return type == MessageType::Ping;
}

void PingHandler::Handle(MessageType type, SharedSpan content)
{
}
