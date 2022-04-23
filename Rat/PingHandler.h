#pragma once

#include "IMessageHandler.h"

class PingHandler : public IMessageHandler
{
public:
	void Handle(std::span<char> content) override;
};

