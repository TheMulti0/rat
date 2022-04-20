#include <iostream>
#include <WinSock2.h>

#include "Trace.h"
#include "Initializer.h"

Initializer::Initializer()
{
	WSADATA wsaData;
	const int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (returnCode != 0) {
		Trace("WSAStartup failed with error: %d\n", returnCode);
		throw std::exception();
	}
}

Initializer::~Initializer()
{
	WSACleanup();
}