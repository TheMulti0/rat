#pragma once

#include "IMessageHandler.h"
#include "IMessageListener.h"
#include "IMessageSender.h"
#include "Screenshotter.h"

class TakeScreenshotHandler : public IMessageHandler
{
public:
	TakeScreenshotHandler(std::shared_ptr<IMessageSender> sender, std::shared_ptr<IMessageListener> ptr);

	void Handle(MessageType type, SharedSpan content) override;

private:
	std::shared_ptr<IMessageSender> _sender;
	Screenshotter _screenshotter;
};

