#include "TakeScreenshotHandler.h"

TakeScreenshotHandler::TakeScreenshotHandler(
	std::shared_ptr<IMessageSender> sender, 
	std::shared_ptr<Screenshotter> screenshotter
) :
	_sender(sender),
	_screenshotter(screenshotter)
{
}

bool TakeScreenshotHandler::CanHandle(const MessageType type)
{
	return type == MessageType::TakeScreenshot;
}

void TakeScreenshotHandler::Handle(MessageType type, SharedSpan content)
{
	_sender->Send(
		MessageType::Screenshot, 
		_screenshotter->ScreenshotScreen());
}
