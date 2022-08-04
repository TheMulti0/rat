#pragma once

#include <memory>
#include <span>

#include "IConnection.h"
#include "IMessageSender.h"

class MessageSender final : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);

	int Send(MessageType type, SharedSpan content) override;

private:
	static SharedSpan CreateMessage(MessageType type, const SharedSpan content);

	int SendAll(const SharedSpan buffer) const;

	IConnection* _connection;
};