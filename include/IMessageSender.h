#pragma once

#include <span>

#include "MessageType.h"
#include "SharedSpan.h"

class IMessageSender
{
public:
	virtual ~IMessageSender() = default;

	virtual int Send(MessageType type, SharedSpan content) = 0;
};
