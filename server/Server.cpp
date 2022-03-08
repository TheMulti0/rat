#include "Server.h"

#include <WS2tcpip.h>
#include <stdexcept>

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
		Unbind();
		throw std::runtime_error(Format("bind failed with error: %d", WSAGetLastError()));
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
		closesocket(_listenSocket);
		throw std::runtime_error(Format("accept failed with error: %d", WSAGetLastError()));
	}

	return new Connection(clientSocket);
}

void Server::ListenForConnections()
{
	int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("listen failed with error: %d", WSAGetLastError()));
	}
}

SOCKET Server::CreateListenSocket()
{
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("socket failed with error: %d", WSAGetLastError()));
	}

	return listenSocket;
}