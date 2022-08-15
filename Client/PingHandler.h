#pragma once

#include "IMessageHandler.h"

class PingHandler : public IMessageHandler
{
public:
	bool CanHandle(MessageType type) override;

	void Handle(MessageType type, SharedSpan content) override;
};

