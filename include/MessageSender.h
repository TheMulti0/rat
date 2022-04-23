#pragma once

#include <memory>
#include <span>

#include "IConnection.h"
#include "IMessageSender.h"

class MessageSender final : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);

	int Send(MessageType type, std::span<char> content) override;

private:
	static std::span<char> CreateMessage(MessageType type, std::span<char> content);

	int SendAll(const char* buffer, int length) const;

	IConnection* _connection;
};