#include <WS2tcpip.h>
#include <stdexcept>

#include "Format.h"
#include "WinSockConnectionListener.h"

WinSockConnectionListener::WinSockConnectionListener(const int port) :
	_addressInfo(std::make_unique<WinSockAddressInfo>(nullptr, port)),
	_addrInfo(_addressInfo->Get()),
	_listenSocket(CreateListenSocket())
{
	Bind();
}

WinSockConnectionListener::~WinSockConnectionListener()
{
	Unbind();
}

void WinSockConnectionListener::Bind() const
{
	const int returnCode = bind(_listenSocket, _addrInfo.ai_addr, static_cast<int>(_addrInfo.ai_addrlen));

	if (returnCode == SOCKET_ERROR)
	{
		Unbind();
		throw std::runtime_error(Format("bind failed with error: %d", WSAGetLastError()));
	}
}

std::unique_ptr<IConnection> WinSockConnectionListener::WaitForConnection()
{
	ListenForConnections();

	return AcceptClientConnection();
}

void WinSockConnectionListener::Unbind() const
{
	closesocket(_listenSocket);
}

std::unique_ptr<IConnection> WinSockConnectionListener::AcceptClientConnection() const
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

void WinSockConnectionListener::ListenForConnections() const
{
	const int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(_listenSocket);
		throw std::runtime_error(Format("listen failed with error: %d", WSAGetLastError()));
	}
}

SOCKET WinSockConnectionListener::CreateListenSocket() const
{
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (listenSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("socket failed with error: %d", WSAGetLastError()));
	}

	return listenSocket;
}
