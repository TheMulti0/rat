#include "TakeScreenshotHandler.h"

TakeScreenshotHandler::TakeScreenshotHandler(std::shared_ptr<IMessageSender> sender, std::shared_ptr<IMessageListener> ptr):
	_sender(sender)
{
}

void TakeScreenshotHandler::Handle(MessageType type, SharedSpan content)
{
	_sender->Send(
		MessageType::Screenshot, 
		_screenshotter.ScreenshotScreen());
}
