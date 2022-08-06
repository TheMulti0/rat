#pragma once

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "Screenshot.h"

class TakeScreenshotHandler : public IMessageHandler
{
public:
	TakeScreenshotHandler(IMessageSender* sender) :
		_sender(sender)
	{
	}

	void Handle(MessageType type, SharedSpan content) override
	{
		_sender->Send(
			MessageType::Screenshot, 
			_screenshot.ScreenshotScreen());
	}

private:
	IMessageSender* _sender;
	Screenshot _screenshot;
};

