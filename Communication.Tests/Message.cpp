#include "Message.h"

Message::Message(const MessageType type, const SharedSpan content):
	_type(type),
	_content(content)
{
}

MessageType Message::GetType() const
{
	return _type;
}

SharedSpan Message::GetContent() const
{
	return _content;
}
