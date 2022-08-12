#pragma once

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "Screenshotter.h"

class TakeScreenshotHandler : public IMessageHandler
{
public:
	TakeScreenshotHandler(IMessageSender* sender);

	void Handle(MessageType type, SharedSpan content) override;

private:
	IMessageSender* _sender;
	Screenshotter _screenshotter;
};

