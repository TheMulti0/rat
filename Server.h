#pragma once

#undef UNICODE

#include "Connection.h"
#include "Config.h"
#include "AddressInfo.h"

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

class Server
{
public:
	Server(int port);

	void Bind();

	Connection* WaitForConnection();

	void Unbind();

private:
	SOCKET CreateListenSocket();

	void ListenForConnections();

	Connection* AcceptClientConnection();

	AddressInfo _addressInfo;
	addrinfo& _addrInfo;
	SOCKET _listenSocket;
};

Server::Server(int port) :
	_addressInfo(nullptr, port),
	_addrInfo(_addressInfo.get()),
	_listenSocket(CreateListenSocket())
{
}

void Server::Bind()
{
	int returnCode = bind(_listenSocket, _addrInfo.ai_addr, (int) _addrInfo.ai_addrlen);

	if (returnCode == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		Unbind();
		throw std::exception();
	}
}

Connection* Server::WaitForConnection()
{
	ListenForConnections();

	return AcceptClientConnection();
}

void Server::Unbind()
{
	closesocket(_listenSocket);
}

Connection* Server::AcceptClientConnection()
{
	auto clientSocket = INVALID_SOCKET;

	clientSocket = accept(_listenSocket, nullptr, nullptr);

	if (clientSocket == INVALID_SOCKET)
	{
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(_listenSocket);
		throw std::exception();
	}

	return new Connection(clientSocket);
}

void Server::ListenForConnections()
{
	int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(_listenSocket);
		throw std::exception();
	}
}

SOCKET Server::CreateListenSocket()
{
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		throw std::exception();
	}

	return listenSocket;
}