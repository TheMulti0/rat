#include "Message.h"

Message::Message(const MessageType type, const std::span<char> content):
	_type(type),
	_content(content)
{
}

MessageType Message::GetType() const
{
	return _type;
}

std::span<char> Message::GetContent() const
{
	return _content;
}
