#include "SingleProcessManager.h"

#include <utility>

SingleProcessManager::SingleProcessManager(
	std::function<void(std::string)> onMessage,
	const bool inheritHandles,
	const bool waitForExit
) :
	_onMessage(std::move(onMessage)),
	_inheritHandles(inheritHandles),
	_waitForExit(waitForExit),
	_thread(std::make_unique<ThreadGuard>(
		std::thread(&SingleProcessManager::ReadOutput, this)))
{
}

void SingleProcessManager::Run(const std::wstring name)
{
	_process.reset();
	_process = std::make_unique<Process>(name, _inheritHandles, _waitForExit);
}

void SingleProcessManager::WriteToStdIn(const std::string text)
{
	if (_process == nullptr)
	{
		return;
	}

	_process->WriteToStdIn(text);
}

void SingleProcessManager::ReadOutput() const
{
	while (true)
	{
		if (_process == nullptr)
		{
			continue;
		}

		_onMessage(_process->ReadFromStd());
	}
}

