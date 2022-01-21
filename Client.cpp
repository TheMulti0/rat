#pragma once

#include "Client.h"
#include "Trace.h"
#include "Connection.h"

//#include <Windows.h>
#include <WS2tcpip.h>

Client::Client(const char* ip, int port) :
		_addressInfo(ip, port),
		_addrInfo(_addressInfo.get())
{
}

Connection* Client::Connect()
{
	auto connectSocket = ConnectToServer();

	if (connectSocket == INVALID_SOCKET)
	{
		Trace("Unable to connect to server!\n");
		throw std::exception();
	}

	return new Connection(connectSocket);
}

SOCKET Client::ConnectToServer()
{
	auto connectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server
	connectSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (connectSocket == INVALID_SOCKET)
	{
		Trace("connectSocket failed with error: %ld\n", WSAGetLastError());
		throw std::exception();
	}

	// Connect to server
	int returnCode = connect(connectSocket, _addrInfo.ai_addr, (int)_addrInfo.ai_addrlen);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(connectSocket);
		return INVALID_SOCKET;
	}

	return connectSocket;
}