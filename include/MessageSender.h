#pragma once

#include "IConnection.h"
#include "IMessageSender.h"

class MessageSender : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);
	int SendAll(const char* buffer, int length) const;
	~MessageSender() override = default;

	bool Send(MessageType type, std::string message) override;

private:
	std::unique_ptr<IConnection> _connection;
};