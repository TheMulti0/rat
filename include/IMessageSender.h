#pragma once

#include <span>

#include "MessageType.h"

class IMessageSender
{
public:
	virtual ~IMessageSender() = default;

	virtual int Send(MessageType type, std::span<char> content) = 0;
};