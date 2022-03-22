#include <iostream>
#include <WinSock2.h>

#include "Trace.h"
#include "WinSockInitializer.h"

WinSockInitializer::WinSockInitializer()
{
	WSADATA wsaData;
	const int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (returnCode != 0) {
		Trace("WSAStartup failed with error: %d\n", returnCode);
		throw std::exception();
	}
}

WinSockInitializer::~WinSockInitializer()
{
	WSACleanup();
}