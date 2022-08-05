#pragma once

#include "IConnection.h"
#include "IMessageSender.h"
#include "MessageQueue.h"

class MessageSender final : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);
	~MessageSender();

	void Send(MessageType type, SharedSpan content) override;

private:
	static SharedSpan CreateMessage(MessageType type, const SharedSpan content);

	int SendAll(const SharedSpan buffer) const;

	IConnection* _connection;
	MessageQueue _queue;
};