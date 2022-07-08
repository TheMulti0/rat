#pragma once

#include <span>

#include "MessageType.h"

class IMessageHandler
{
public:
	virtual ~IMessageHandler() = default;

	virtual void Handle(MessageType type, std::span<char> content) = 0;
};
