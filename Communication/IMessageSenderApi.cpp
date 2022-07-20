#include "IMessageSenderApi.h"

int Send(
	IMessageSender* sender,
	const MessageType type, 
	char* content,
	const int contentLength)
{
	const auto contentSpan = std::span(content, contentLength);

	return sender->Send(type, contentSpan);
}
