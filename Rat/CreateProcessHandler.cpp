#include <string>

#include "CreateProcessHandler.h"

void CreateProcessHandler::Handle(std::span<char> content)
{
	const auto message = std::string(content.begin(), content.end());
	wchar_t wMessage[20];

	size_t sizeInWords = message.length();
	mbstowcs_s(&sizeInWords, wMessage, message.c_str(), sizeInWords);

	Create(wMessage);
}

void CreateProcessHandler::Create(const LPWSTR name)
{
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof startupInfo);
	startupInfo.cb = sizeof startupInfo;

	PROCESS_INFORMATION processInfo;
	ZeroMemory(&processInfo, sizeof processInfo);

	const auto result = CreateProcess(
		nullptr, // No module name (use command line)
		name, // Command line
		nullptr, // Process handle not inheritable
		nullptr, // Thread handle not inheritable
		false, // Set handle inheritance to FALSE
		0, // No creation flags
		nullptr, // Use parent's environment block
		nullptr, // Use parent's starting directory 
		&startupInfo,
		&processInfo
	);

	if (!result)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}
