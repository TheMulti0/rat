#pragma once

#include <map>

#include "ICommunicationFactory.h"
#include "IMessageHandler.h"
#include "IRat.h"
#include "Hypodermic/Hypodermic.h"

class Rat : public IRat
{
public:
	Rat(
		ICommunicationFactory* factory,
		const char* ip,
		int port);

private:
	std::shared_ptr<Hypodermic::Container> CreateContainer(
		ICommunicationFactory* factory,
		const char* ip,
		int port);

	std::map<MessageType, std::shared_ptr<IMessageHandler>> GetHandlers() const;

	void OnMessage(MessageType type, SharedSpan content);
	void OnDisconnection();

	std::shared_ptr<Hypodermic::Container> _container;
	std::shared_ptr<IConnectionFactory> _client;
	std::shared_ptr<IConnection> _connection;
	std::shared_ptr<IMessageSender> _sender;
	std::shared_ptr<IMessageListener> _listener;
	std::map<MessageType, std::shared_ptr<IMessageHandler>> _handlers;
};
