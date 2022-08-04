#pragma once

#include <span>

#include "MessageType.h"
#include "SharedSpan.h"

class Message
{
public:
	static Message Deserialize(SharedSpan buffer);
	[[nodiscard]] SharedSpan Serialize();

	Message(MessageType type, SharedSpan content);

	MessageType GetType() const;
	[[nodiscard]] SharedSpan GetContent() const;

private:
	MessageType _type;
	SharedSpan _content;
};
