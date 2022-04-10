#pragma once

#include <string>

class IMessageHandler
{
public:
	virtual ~IMessageHandler() = default;

	virtual void Handle(std::string message) = 0;
};
