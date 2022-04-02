#pragma once

#include <memory>

#include "IConnection.h"
#include "Message.h"

class IMessageListener
{
public:
	virtual ~IMessageListener() = default;
};

__declspec(dllexport)
std::unique_ptr<IMessageListener> CreateMessageListener(
	IConnection* connection,
	void (*onMessage)(MessageType, std::string));