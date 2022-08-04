#pragma once

#include "MessageType.h"
#include "SharedSpan.h"

class IMessageHandler
{
public:
	virtual ~IMessageHandler() = default;

	virtual void Handle(MessageType type, SharedSpan content) = 0;
};
