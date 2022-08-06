#pragma once

#include "IConnection.h"
#include "IMessageSender.h"
#include "IOperationQueue.h"

class MessageSender final : public IMessageSender
{
public:
	explicit MessageSender(IConnection* connection);

	void Send(MessageType type, SharedSpan content) override;

private:
	static SharedSpan CreateMessage(MessageType type, const SharedSpan content);

	[[nodiscard]] int SendAll(SharedSpan buffer) const;

	IConnection* _connection;
	std::unique_ptr<IOperationQueue> _queue;
};