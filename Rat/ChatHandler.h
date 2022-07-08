#pragma once

#include "IMessageHandler.h"

class ChatHandler : public IMessageHandler
{
public:
	void Handle(MessageType type, std::span<char> content) override;
};

