#pragma once

#include "Windows.h"
#include <string>

#include "Pipe.h"
#include "UniqueHandle.h"

class Process
{
public:
	Process(
		const std::wstring& name, 
		bool inheritHandles,
		bool waitForExit);
	~Process();

	void WriteToStdIn(std::string buffer) const;

	[[nodiscard]] std::string ReadFromStd() const;

private:
	void Join() const;
	void Kill() const;

	static SECURITY_ATTRIBUTES CreateSecurityAttributes();
	static PROCESS_INFORMATION CreateProcessInfo();
	STARTUPINFO CreateStartupInfo() const;
	void Create(
		const std::wstring& name,
		bool inheritHandles);

	DWORD GetBytesAvailable() const;
	DWORD Read(
		char* buffer,
		int bufferSize) const;
	DWORD Read(
		DWORD bytesAvailable,
		int bufferSize,
		std::string& output) const;

	bool _waitForExit;
	SECURITY_ATTRIBUTES _securityAttributes;
	PROCESS_INFORMATION _processInfo;
	Pipe _stdIn;
	Pipe _stdOut;
	STARTUPINFO _startupInfo;
	UniqueHandle _processHandle;
	UniqueHandle _threadHandle;
};
