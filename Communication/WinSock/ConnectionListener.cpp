#include <WS2tcpip.h>
#include <stdexcept>

#include "ConnectionListener.h"
#include "Connection.h"
#include "ErrorExtensions.h"

ConnectionListener::ConnectionListener(const int port) :
	_addressInfo(std::make_unique<AddressInfo>(nullptr, port)),
	_addrInfo(_addressInfo->Get()),
	_listenSocket(CreateListenSocket())
{
	const int returnCode = bind(_listenSocket, _addrInfo.ai_addr, static_cast<int>(_addrInfo.ai_addrlen));
	if (returnCode == SOCKET_ERROR)
	{
		ThrowWinApiException("Socket bind failed");
	}
}

ConnectionListener::~ConnectionListener()
{
	closesocket(_listenSocket);
}

std::unique_ptr<IConnection> ConnectionListener::WaitForConnection()
{
	ListenForConnections();

	return AcceptClientConnection();
}

std::unique_ptr<IConnection> ConnectionListener::AcceptClientConnection() const
{
	sockaddr_in address;
	int addressLen = sizeof address;

	auto clientSocket = accept(_listenSocket, reinterpret_cast<sockaddr*>(&address), &addressLen);

	if (clientSocket == INVALID_SOCKET)
	{
		ThrowWinApiException("Client socket accept failed");
	}

	return std::make_unique<Connection>(clientSocket, address);
}

void ConnectionListener::ListenForConnections() const
{
	const int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		ThrowWinApiException("Failed to listen for connections");
	}
}

SOCKET ConnectionListener::CreateListenSocket() const
{
	const auto listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		ThrowWinApiException("Failed to create the socket for listening to connections");
	}

	return listenSocket;
}
