#pragma once

#include <span>

#include "IConnection.h"
#include "IMessageSender.h"

class MessageSender : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);
	~MessageSender() override = default;

	bool Send(const MessageType type, const std::span<char> content) override;

private:
	static std::span<char> CreateMessage(const MessageType type, const std::span<char> content);
	int SendAll(const char* buffer, int length) const;
	std::unique_ptr<IConnection> _connection;
};