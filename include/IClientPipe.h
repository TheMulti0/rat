#pragma once

#include "IConnection.h"
#include "IMessageListener.h"
#include "IMessageSender.h"

class IClientPipe
{
public:
	virtual ~IClientPipe() = default;

	[[nodiscard]] virtual IConnection* GetConnection() const = 0;
	[[nodiscard]] virtual IMessageSender* GetSender() const = 0;
	[[nodiscard]] virtual IMessageListener* GetListener() const = 0;
};

