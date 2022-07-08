#include "Process.h"

Process::Process(
	const std::wstring& name, 
	bool inheritHandles,
	const bool waitForExit
) :
	_waitForExit(waitForExit)
{
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = nullptr;

	CreatePipe(&_stdOutRead, &_stdOutWrite, &saAttr, 0);
	SetHandleInformation(_stdOutRead, HANDLE_FLAG_INHERIT, 0);

	CreatePipe(&_stdInRead, &_stdInWrite, &saAttr, 0);
	SetHandleInformation(_stdOutRead, HANDLE_FLAG_INHERIT, 0);

	constexpr size_t startupInfoSize = sizeof STARTUPINFO;
	_startupInfo = std::make_unique<STARTUPINFO>();

	std::memset(_startupInfo.get(), 0, startupInfoSize);
	_startupInfo->cb = startupInfoSize;
	_startupInfo->hStdError = _stdOutWrite;
	_startupInfo->hStdOutput = _stdOutWrite;
	_startupInfo->hStdInput = _stdInRead;
	_startupInfo->dwFlags |= STARTF_USESTDHANDLES;

	_processInfo = std::make_unique<PROCESS_INFORMATION>();
	std::memset(_processInfo.get(), 0, sizeof PROCESS_INFORMATION);

	const auto result = CreateProcess(
		nullptr, // No module name (use command line)
		const_cast<LPWSTR>(name.c_str()), // Command line
		nullptr, // Process handle not inheritable
		nullptr, // Thread handle not inheritable
		inheritHandles,
		CREATE_NO_WINDOW, // creation flags
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

void Process::WriteToStdIn(std::string& buffer) const
{
	buffer += '\n';
	DWORD dwWritten = 0;

	bool result = WriteFile(
		_stdInWrite, 
		buffer.c_str(),
		buffer.size(),
		&dwWritten, 
		nullptr);
}

std::string Process::ReadFromStdOut() const
{
	DWORD bytesAvailable = 0;
	DWORD bytesRead = 0;
	int intBytesAvailable = 0;
	char buffer[128] = "";
	std::string output;

	do		//loop until bytes are available (until response is processed)
	{
		PeekNamedPipe(_stdOutRead, nullptr, 0, nullptr, &bytesAvailable, nullptr);
		Sleep(50);
	} while (bytesAvailable <= 0);
	/*
	if (bytesAvailable >= 2048)
		bytesAvailable = 2048;
		*/
	intBytesAvailable = bytesAvailable;
	while (intBytesAvailable > 0)		//while there is something to read, read it into buffer and append buffer to string
	{
		ReadFile(_stdOutRead, buffer, 127, &bytesRead, nullptr);
		buffer[127] = '\0';	//NULL terminator of string
		output += buffer;
		intBytesAvailable -= bytesRead;
		if (intBytesAvailable <= 0)
			intBytesAvailable = 0;
		ZeroMemory(buffer, 128);					//clears buffer (else memory leak)
	}

	return output;
}

void Process::Join() const
{
	WaitForSingleObject(_processInfo->hProcess, INFINITE);
}
