#pragma once

#include <functional>
#include <memory>
#include <string>

class ISingleProcessManager
{
public:
	virtual ~ISingleProcessManager() = default;

	virtual void Run(std::wstring name) = 0;

	virtual void WriteToStdIn(std::string text) = 0;
};

__declspec(dllexport)
std::unique_ptr<ISingleProcessManager> CreateSingleProcessManager(
	const std::function<void(std::string)>& onMessage,
	bool inheritHandles,
	bool waitForExit);