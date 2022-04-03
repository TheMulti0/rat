#include <WS2tcpip.h>
#include <stdexcept>

#include "Format.h"
#include "IConnection.h"
#include "WinSockConnectionFactory.h"

WinSockConnectionFactory::WinSockConnectionFactory(const char* ip, const int port) :
	_addressInfo(std::make_unique<WinSockAddressInfo>(ip, port)),
	_addrInfo(_addressInfo->Get())
{
}

std::unique_ptr<IConnection> WinSockConnectionFactory::Connect()
{
	const auto connectSocket = ConnectToServer();

	if (connectSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("Unable to connect to server!"));
	}

	return CreateWinSockConnection(connectSocket);
}

SOCKET WinSockConnectionFactory::ConnectToServer() const
{
	auto connectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server
	connectSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (connectSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("connectSocket failed with error: %d", WSAGetLastError()));
	}

	// Connect to server
	const int returnCode = connect(connectSocket, _addrInfo.ai_addr, (int)_addrInfo.ai_addrlen);

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(connectSocket);
		return INVALID_SOCKET;
	}

	return connectSocket;
}
