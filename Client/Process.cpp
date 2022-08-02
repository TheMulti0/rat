#include "Process.h"

#include <stdexcept>

#include "ErrorExtensions.h"
#include "UniqueHandle.h"

Process::Process(
	const std::wstring& name,
	const bool inheritHandles,
	const bool waitForExit
) :
	_waitForExit(waitForExit),
	_securityAttributes(CreateSecurityAttributes()),
	_processInfo(CreateProcessInfo()),
	_stdIn(Pipe(_securityAttributes)),
	_stdOut(Pipe(_securityAttributes)),
	_startupInfo(CreateStartupInfo())
{
	Create(name, inheritHandles);

	_processHandle = UniqueHandle(_processInfo.hProcess);
	_threadHandle = UniqueHandle(_processInfo.hThread);
}

Process::~Process()
{
	if (_waitForExit)
	{
		Join();
	}
	else
	{
		Kill();
	}
}

void Process::WriteToStdIn(std::string buffer) const
{
	buffer += '\n';
	DWORD dwWritten = 0;

	if (!WriteFile(
		_stdIn.Write(), 
		buffer.c_str(),
		buffer.size(),
		&dwWritten, 
		nullptr))
	{
		ThrowWinApiException("Failed to write to std in");
	}
}

std::string Process::ReadFromStd() const
{
	DWORD bytesAvailable = 0;

	do
	{
		bytesAvailable = GetBytesAvailable();
		Sleep(50);
	}
	while (bytesAvailable <= 0);

	std::string output;
	while (bytesAvailable > 0)
	{
		constexpr int bufferSize = 128;
		bytesAvailable = Read(bytesAvailable, bufferSize, output);
	}

	return output;
}

void Process::Join() const
{
	const DWORD result = WaitForSingleObject(*_processHandle, INFINITE);

	if (result == WAIT_FAILED)
	{
		ThrowWinApiException("Waiting for process has failed");
	}
}

void Process::Kill() const
{
	const auto result = TerminateProcess(*_processHandle, 1);

	if (!result)
	{
		ThrowWinApiException("Process termination failed");
	}
}

SECURITY_ATTRIBUTES Process::CreateSecurityAttributes()
{
	SECURITY_ATTRIBUTES securityAttributes;

	securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.lpSecurityDescriptor = nullptr;

	return securityAttributes;
}

PROCESS_INFORMATION Process::CreateProcessInfo()
{
	PROCESS_INFORMATION processInfo;

	std::memset(&processInfo, 0, sizeof PROCESS_INFORMATION);

	return processInfo;
}

STARTUPINFO Process::CreateStartupInfo() const
{
	constexpr size_t startupInfoSize = sizeof STARTUPINFO;

	STARTUPINFO startupInfo;

	std::memset(&startupInfo, 0, startupInfoSize);

	startupInfo.cb = startupInfoSize;
	startupInfo.hStdError = _stdOut.Write();
	startupInfo.hStdOutput = _stdOut.Write();
	startupInfo.hStdInput = _stdIn.Read();
	startupInfo.dwFlags |= STARTF_USESTDHANDLES;

	return startupInfo;
}

void Process::Create(
	const std::wstring& name,
	const bool inheritHandles)
{
	bool result = CreateProcessW(
		nullptr, // No module name (use command line)
		const_cast<LPWSTR>(name.c_str()), // Command line
		nullptr, // Process handle not inheritable
		nullptr, // Thread handle not inheritable
		inheritHandles,
		CREATE_NO_WINDOW, // creation flags
		nullptr, // Use parent's environment block
		nullptr, // Use parent's starting directory 
		&_startupInfo,
		&_processInfo
	);

	if (!result)
	{
		ThrowWinApiException("Create process failed");
	}
}

DWORD Process::GetBytesAvailable() const
{
	DWORD bytesAvailable = 0;

	if (!PeekNamedPipe(
		_stdOut.Read(),
		nullptr, 
		0, 
		nullptr, 
		&bytesAvailable, 
		nullptr))
	{
		ThrowWinApiException("Failed to get bytes available from std out");
	}

	return bytesAvailable;
}

DWORD Process::Read(
	char* buffer,
	const int bufferSize) const
{
	DWORD bytesRead = 0;

	if (!ReadFile(
		_stdOut.Read(),
		buffer,
		bufferSize,
		&bytesRead,
		nullptr))
	{
		ThrowWinApiException("Failed to read from std out");
	}

	return bytesRead;
}

DWORD Process::Read(
	const DWORD bytesAvailable,
	const int bufferSize, 
	std::string& output) const
{
	const int actualSize = bufferSize + 1;
	const auto buffer = std::make_unique<char[]>(actualSize);

	const DWORD bytesRead = Read(buffer.get(), bufferSize);

	buffer[actualSize - 1] = '\0';
	output += buffer.get();

	const DWORD remainder = bytesAvailable - bytesRead;
	return max(remainder, 0);
}
