#pragma once

#include "ICommunicationFactory.h"
#include "Hypodermic/Hypodermic.h"

class CommunicationContainerBuilder :public Hypodermic::ContainerBuilder
{
public:
	CommunicationContainerBuilder(
		std::shared_ptr<ICommunicationFactory> factory,
		const char* ip, 
		int port);

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
