#include "MessagesHandler.h"

MessagesHandler::MessagesHandler(
	ICommunicationFactory* rat,
	IConnection* connection,
	std::map<MessageType, std::unique_ptr<IMessageHandler>>* map
) :
_listener(
	rat->CreateMessageListener(
		connection, 
		[this](auto type, auto message) { OnMessage(type, message); },
		[]{})),
_map(map)
{
}

void MessagesHandler::OnMessage(const MessageType type, std::span<char> content) const
{
	(* _map)[type]->Handle(content);
}


//std::unique_ptr<IMessagesHandler> CreateMessagesHandler(IConnection* connection)
//{
//	std::map<MessageType, std::unique_ptr<IMessageHandler>> map;
//	map[MessageType::Chat] = std::make_unique<ChatHandler>();
//
//	return std::make_unique<MessagesHandler>(this, connection, &map);
//}