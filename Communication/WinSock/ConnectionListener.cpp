#include <WS2tcpip.h>
#include <stdexcept>

#include "Format.h"
#include "ConnectionListener.h"
#include "Connection.h"

ConnectionListener::ConnectionListener(const int port) :
	_addressInfo(std::make_unique<AddressInfo>(nullptr, port)),
	_addrInfo(_addressInfo->Get()),
	_listenSocket(CreateListenSocket())
{
	Bind();
}

ConnectionListener::~ConnectionListener()
{
	Unbind();
}

void ConnectionListener::Bind() const
{
	const int returnCode = bind(_listenSocket, _addrInfo.ai_addr, static_cast<int>(_addrInfo.ai_addrlen));

	if (returnCode == SOCKET_ERROR)
	{
		Unbind();
		throw std::runtime_error(Format("bind failed with error: %d", WSAGetLastError()));
	}
}

std::unique_ptr<IConnection> ConnectionListener::WaitForConnection()
{
	ListenForConnections();

	return AcceptClientConnection();
}

void ConnectionListener::Unbind() const
{
	closesocket(_listenSocket);
}

std::unique_ptr<IConnection> ConnectionListener::AcceptClientConnection() const
{
	auto clientSocket = accept(_listenSocket, nullptr, nullptr);

	if (clientSocket == INVALID_SOCKET)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("accept failed with error: %d", WSAGetLastError()));
	}

	return std::make_unique<Connection>(clientSocket);
}

void ConnectionListener::ListenForConnections() const
{
	const int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("listen failed with error: %d", WSAGetLastError()));
	}
}

SOCKET ConnectionListener::CreateListenSocket() const
{
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("socket failed with error: %d", WSAGetLastError()));
	}

	return listenSocket;
}
