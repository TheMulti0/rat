#pragma once

#include <memory>
#include <span>

#include "IMessageHandler.h"
#include "ISingleProcessManager.h"

class CreateProcessHandler : public IMessageHandler
{
public:
	CreateProcessHandler();

	void Handle(MessageType type, SharedSpan content) override;

private:
	std::unique_ptr<ISingleProcessManager> _manager;
};
