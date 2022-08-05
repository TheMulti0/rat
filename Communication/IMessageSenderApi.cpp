#include "IMessageSenderApi.h"

void Send(
	IMessageSender* sender,
	const MessageType type, 
	char* content,
	const int contentLength)
{
	auto contentSpan = SharedSpan(contentLength);

	std::copy_n(content, contentLength, contentSpan.Data());

	sender->Send(type, contentSpan);
}
