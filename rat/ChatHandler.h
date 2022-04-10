#pragma once

#include "IMessageHandler.h"

class ChatHandler : public IMessageHandler
{
public:
	void Handle(std::string message) override;
};

