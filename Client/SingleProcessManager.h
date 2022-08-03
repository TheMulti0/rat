#pragma once

#include <functional>

#include "ISingleProcessManager.h"
#include "Process.h"
#include "IThreadGuard.h"

class SingleProcessManager : public ISingleProcessManager
{
public:
	SingleProcessManager(
		std::function<void(std::string)> onMessage,
		bool inheritHandles,
		bool waitForExit);

	void Run(std::wstring name) override;

	void WriteToStdIn(std::string text) override;

private:
	void ReadOutput() const;

	std::function<void(std::string)> _onMessage;
	bool _inheritHandles;
	bool _waitForExit;
	std::unique_ptr<IThreadGuard> _thread;
	std::unique_ptr<Process> _process;
};

