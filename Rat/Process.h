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

	void WriteToStdIn(std::string& buffer) const;

	[[nodiscard]] std::string ReadFromStdOut() const;

private:
	void Join() const;
	void Kill() const;

	bool _waitForExit;
	HANDLE _stdInRead{};
	HANDLE _stdInWrite{};
	HANDLE _stdOutRead{};
	HANDLE _stdOutWrite{};
	std::unique_ptr<STARTUPINFO> _startupInfo;
	std::unique_ptr<PROCESS_INFORMATION> _processInfo;
};
