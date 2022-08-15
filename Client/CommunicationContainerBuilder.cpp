#include "CommunicationContainerBuilder.h"

CommunicationContainerBuilder::CommunicationContainerBuilder(
	std::shared_ptr<ICommunicationFactory> factory,
	const char* ip,
	const int port)
{
	registerInstance(factory);

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
}
