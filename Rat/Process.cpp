#include "Process.h"

Process::Process(
	const std::wstring& name, 
	bool inheritHandles,
	const bool waitForExit
) :
	_waitForExit(waitForExit)
{
	constexpr size_t startupInfoSize = sizeof *_startupInfo;
	std::memset(_startupInfo.get(), 0, startupInfoSize);
	_startupInfo->cb = startupInfoSize;

	std::memset(_processInfo.get(), 0, startupInfoSize);

	const auto result = CreateProcess(
		nullptr, // No module name (use command line)
		const_cast<LPWSTR>(name.c_str()), // Command line
		nullptr, // Process handle not inheritable
		nullptr, // Thread handle not inheritable
		inheritHandles,
		0, // No creation flags
		nullptr, // Use parent's environment block
		nullptr, // Use parent's starting directory 
		_startupInfo.get(),
		_processInfo.get()
	);

	if (!result)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
}

Process::~Process()
{
	if (_waitForExit)
	{
		Join();
	}

	CloseHandle(_processInfo->hProcess);
	CloseHandle(_processInfo->hThread);
}

void Process::Join() const
{
	WaitForSingleObject(_processInfo->hProcess, INFINITE);
}
