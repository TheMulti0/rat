#include <WS2tcpip.h>
#include <stdexcept>

#include "Client.h"
#include "Format.h"
#include "IConnection.h"

Client::Client(const char* ip, const int port) :
		_addressInfo(CreateAddressInfo(ip, port)),
		_addrInfo(_addressInfo->Get())
{
}

std::unique_ptr<IConnection> Client::Connect() const
{
	const auto connectSocket = ConnectToServer();

	if (connectSocket == INVALID_SOCKET)
	{
		throw std::runtime_error(Format("Unable to connect to server!"));
	}

	return CreateWinSockConnection(connectSocket);
}

SOCKET Client::ConnectToServer() const
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
