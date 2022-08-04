#pragma once

#include <span>

#include "MessageType.h"
#include "SharedSpan.h"

class Message
{
public:
	Message(MessageType type, SharedSpan content);

	[[nodiscard]] MessageType GetType() const;

	[[nodiscard]] SharedSpan GetContent() const;

private:
	MessageType _type;
	SharedSpan _content;
};
