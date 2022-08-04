#pragma once

#include "IMessageHandler.h"

class ChatHandler : public IMessageHandler
{
public:
	void Handle(MessageType type, SharedSpan content) override;
};

