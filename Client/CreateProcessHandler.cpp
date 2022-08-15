#include <string>

#include "CreateProcessHandler.h"

#include "SingleProcessManager.h"
#include "StringExtensions.h"

CreateProcessHandler::CreateProcessHandler()
	: _manager(
		CreateSingleProcessManager(
			[](const std::string& _) {},
			false,
			true))
{
}

bool CreateProcessHandler::CanHandle(const MessageType type)
{
	return type == MessageType::CreateProcessS;
}

void CreateProcessHandler::Handle(MessageType type, SharedSpan content)
{
	const auto name = ToWString(content.String());

	_manager->Run(name);
}
