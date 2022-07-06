#pragma once

#include "Windows.h"
#include <memory>
#include <string>

class Process
{
public:
	Process(
		const std::wstring& name, 
		bool inheritHandles,
		bool waitForExit);
	~Process();

private:
	void Join() const;

	bool _waitForExit;
	std::unique_ptr<STARTUPINFO> _startupInfo;
	std::unique_ptr<PROCESS_INFORMATION> _processInfo;
};
