#include <string>

#include "CreateProcessHandler.h"

#include "SingleProcessManager.h"

CreateProcessHandler::CreateProcessHandler()
	: _manager(
		CreateSingleProcessManager(
			[](const std::string& _) {},
			false,
			true))
{
}

void CreateProcessHandler::Handle(MessageType type, std::span<char> content)
{
	const auto name = std::wstring(content.begin(), content.end());

	_manager->Run(name);
}
