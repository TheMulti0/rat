#pragma once

#include <span>

class IMessageHandler
{
public:
	virtual ~IMessageHandler() = default;

	virtual void Handle(std::span<char> content) = 0;
};
