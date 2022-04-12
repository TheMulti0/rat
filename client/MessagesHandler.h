#pragma once

#include <map>

#include "IMessageHandler.h"
#include "IMessagesHandler.h"
#include "IRat.h"
#include "MessageType.h"

class MessagesHandler : public IMessagesHandler
{
public:
	MessagesHandler(
		IRat* rat,
		IConnection* connection,
		std::map<MessageType, std::unique_ptr<IMessageHandler>>* map);

private:
	void OnMessage(MessageType type, std::span<char> content) const;

	std::unique_ptr<IMessageListener> _listener;
	std::map<MessageType, std::unique_ptr<IMessageHandler>>* _map;
};

std::unique_ptr<IMessagesHandler> CreateMessagesHandler(IConnection* connection);