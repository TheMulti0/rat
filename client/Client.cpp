#pragma once

#include "Client.h"
#include "../shared/Format.h"
#include "../shared/Connection.h"

#include <WS2tcpip.h>
#include <stdexcept>

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
		throw std::runtime_error(Format("Unable to connect to server!"));
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
		throw std::runtime_error(Format("connectSocket failed with error: %d", WSAGetLastError()));
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