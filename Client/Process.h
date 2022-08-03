#pragma once

#include <mutex>
#include <string>
#include "Windows.h"
#include <wil/resource.h>

#include "Pipe.h"

class Process
{
public:
	Process(
		const std::wstring& name, 
		bool inheritHandles,
		bool waitForExit);
	~Process();

	void WriteToStdIn(std::string buffer);

	[[nodiscard]] std::string ReadFromStd();

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
	wil::unique_process_information _processInfo;
	Pipe _stdIn;
	Pipe _stdOut;
	STARTUPINFO _startupInfo;
	std::mutex _readMutex;
	std::mutex _writeMutex;
};
