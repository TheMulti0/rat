#pragma once

#include <span>

#include "IMessageHandler.h"

class CreateProcessHandler : public IMessageHandler
{
public:
	void Handle(MessageType type, std::span<char> content) override;
};
