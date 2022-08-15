#pragma once

#include <memory>

#include "IMessageHandler.h"
#include "ISingleProcessManager.h"

class CreateProcessHandler : public IMessageHandler
{
public:
	CreateProcessHandler();

	bool CanHandle(MessageType type) override;

	void Handle(MessageType type, SharedSpan content) override;

private:
	std::unique_ptr<ISingleProcessManager> _manager;
};
