#pragma once

#include "IMessageHandler.h"

class ChatHandler : public IMessageHandler
{
public:
	void Handle(std::span<char> content) override;
};

