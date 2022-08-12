#include "TakeScreenshotHandler.h"

TakeScreenshotHandler::TakeScreenshotHandler(IMessageSender* sender):
	_sender(sender)
{
}

void TakeScreenshotHandler::Handle(MessageType type, SharedSpan content)
{
	_sender->Send(
		MessageType::Screenshot, 
		_screenshotter.ScreenshotScreen());
}
