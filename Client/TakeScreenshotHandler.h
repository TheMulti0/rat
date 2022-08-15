#pragma once

#include "IMessageHandler.h"
#include "IMessageListener.h"
#include "IMessageSender.h"
#include "Screenshotter.h"

class TakeScreenshotHandler : public IMessageHandler
{
public:
	TakeScreenshotHandler(
		std::shared_ptr<IMessageSender> sender, 
		std::shared_ptr<Screenshotter> screenshotter);

	bool CanHandle(MessageType type) override;

	void Handle(MessageType type, SharedSpan content) override;

private:
	std::shared_ptr<IMessageSender> _sender;
	std::shared_ptr<Screenshotter> _screenshotter;
};

