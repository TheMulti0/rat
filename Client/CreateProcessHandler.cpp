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

void CreateProcessHandler::Handle(MessageType type, SharedSpan content)
{
	const auto name = ToWString(content.String());

	_manager->Run(name);
}
