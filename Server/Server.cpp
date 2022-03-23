#include <WS2tcpip.h>
#include <stdexcept>

#include "Server.h"

#include "Format.h"

Server::Server(const int port) :
		_addressInfo(CreateAddressInfo(nullptr, port)),
		_addrInfo(_addressInfo->Get()),
		_listenSocket(CreateListenSocket())
{
	Bind();
}

Server::~Server()
{
	Unbind();
}

void Server::Bind() const
{
	const int returnCode = bind(_listenSocket, _addrInfo.ai_addr, static_cast<int>(_addrInfo.ai_addrlen));

	if (returnCode == SOCKET_ERROR)
	{
		Unbind();
		throw std::runtime_error(Format("bind failed with error: %d", WSAGetLastError()));
	}
}

std::unique_ptr<IConnection> Server::WaitForConnection() const
{
	ListenForConnections();

	return AcceptClientConnection();
}

void Server::Unbind() const
{
	closesocket(_listenSocket);
}

std::unique_ptr<IConnection> Server::AcceptClientConnection() const
{
	auto clientSocket = INVALID_SOCKET;

	clientSocket = accept(_listenSocket, nullptr, nullptr);

	if (clientSocket == INVALID_SOCKET)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("accept failed with error: %d", WSAGetLastError()));
	}

	return CreateWinSockConnection(clientSocket);
}

void Server::ListenForConnections() const
{
	const int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("listen failed with error: %d", WSAGetLastError()));
	}
}

SOCKET Server::CreateListenSocket() const
{
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("socket failed with error: %d", WSAGetLastError()));
	}

	return listenSocket;
}
