﻿#pragma once

#include "IConnection.h"
#include "IMessageSender.h"

class MessageSender : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);
	~MessageSender() override = default;

	bool Send(MessageType type, std::string message) override;

private:
	int SendAll(const char* buffer, int length) const;
	std::unique_ptr<IConnection> _connection;
};