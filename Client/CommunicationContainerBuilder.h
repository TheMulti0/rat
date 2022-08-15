#pragma once

#include "ICommunicationFactory.h"
#include "Hypodermic/Hypodermic.h"

class CommunicationContainerBuilder : public Hypodermic::ContainerBuilder
{
public:
	CommunicationContainerBuilder(
		ICommunicationFactory* factory,
		const char* ip, 
		int port,
		OnMessage onMessage,
		OnDisconnection onDisconnection);

private:
	template <typename T>
	static std::shared_ptr<T> ToShared(std::unique_ptr<T> unique)
	{
		return std::shared_ptr<T>(unique.release());
	}

	template <typename T>
	void Register(std::function<std::unique_ptr<T>(Hypodermic::ComponentContext&)> factory)
	{
		registerInstanceFactory([=](Hypodermic::ComponentContext& context)
		{
			return ToShared(factory(context));
		}).singleInstance();
	}
};
