#include "Server.h"
#include "Trace.h"
#include "Connection.h"

#include <WS2tcpip.h>

Server::Server(int port) :
		_addressInfo(nullptr, port),
		_addrInfo(_addressInfo.get()),
		_listenSocket(CreateListenSocket())
{
	Bind();
}

Server::~Server()
{
	Unbind();
}

void Server::Bind()
{
	int returnCode = bind(_listenSocket, _addrInfo.ai_addr, (int) _addrInfo.ai_addrlen);

	if (returnCode == SOCKET_ERROR)
	{
		Trace("bind failed with error: %d\n", WSAGetLastError());
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
		Trace("accept failed with error: %d\n", WSAGetLastError());
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
		Trace("listen failed with error: %d\n", WSAGetLastError());
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
		Trace("socket failed with error: %ld\n", WSAGetLastError());
		throw std::exception();
	}

	return listenSocket;
}