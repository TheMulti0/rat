#pragma once

#include <string>

#include "MessageType.h"

class IMessageSender
{
public:
	virtual ~IMessageSender() = default;

	virtual bool Send(MessageType type, std::string message) = 0;
};

__declspec(dllexport)
std::unique_ptr<IMessageSender> CreateMessageSender(IConnection* connection);