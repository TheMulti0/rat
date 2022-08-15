#include "CommunicationContainerBuilder.h"

CommunicationContainerBuilder::CommunicationContainerBuilder(
	ICommunicationFactory* factory, 
	const char* ip,
	const int port,
	const OnMessage onMessage,
	const OnDisconnection onDisconnection)
{
	Register<IConnectionFactory>([=](Hypodermic::ComponentContext&)
	{
		return factory->CreateWinSockConnectionFactory(ip, port);
	});

	Register<IConnection>([=](Hypodermic::ComponentContext& context)
	{
		return context.resolve<IConnectionFactory>()->Connect();
	});

	Register<IMessageSender>([=](Hypodermic::ComponentContext& context)
	{
		return factory->CreateMessageSender(
			context.resolve<IConnection>().get());
	});

	Register<IMessageListener>([=](Hypodermic::ComponentContext& context)
	{
		return factory->CreateMessageListener(
			context.resolve<IConnection>().get(),
			onMessage,
			onDisconnection);
	});
}
