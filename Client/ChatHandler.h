#pragma once

#include "IMessageHandler.h"

class ChatHandler : public IMessageHandler
{
public:
	bool CanHandle(MessageType type) override;

	void Handle(MessageType type, SharedSpan content) override;
};

