#pragma once

#include "MessageType.h"
#include "SharedSpan.h"

class IMessageSender
{
public:
	virtual ~IMessageSender() = default;

	virtual void Send(MessageType type, SharedSpan content) = 0;
};
