#pragma once

#include "IMessageHandler.h"

class PingHandler : public IMessageHandler
{
public:
	void Handle(MessageType type, std::span<char> content) override;
};

