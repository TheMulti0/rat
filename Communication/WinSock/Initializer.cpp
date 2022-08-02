#include <WinSock2.h>

#include "Initializer.h"
#include "ErrorExtensions.h"

Initializer::Initializer()
{
	WSADATA wsaData;
	const int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (returnCode != 0) 
	{
		ThrowWinApiException("WSAStartup failed");
	}
}

Initializer::~Initializer()
{
	const int returnCode = WSACleanup();

	if (returnCode != 0)
	{
		ThrowWinApiException("WSAStartup failed");
	}
}