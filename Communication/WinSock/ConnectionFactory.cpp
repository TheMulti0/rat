#include <WS2tcpip.h>
#include <stdexcept>

#include "Format.h"
#include "IConnection.h"
#include "ConnectionFactory.h"
#include "Connection.h"
#include "ErrorExtensions.h"

ConnectionFactory::ConnectionFactory(const char* ip, const int port) :
	_address(Format("%s:%d", ip, port)),
	_addressInfo(std::make_unique<AddressInfo>(ip, port)),
	_addrInfo(_addressInfo->Get())
{
}

std::unique_ptr<IConnection> ConnectionFactory::Connect()
{
	const auto connectSocket = ConnectToServer();

	if (connectSocket == INVALID_SOCKET)
	{
		Sleep(1000);
		return Connect();
	}

	return std::make_unique<Connection>(connectSocket, _address);
}

SOCKET ConnectionFactory::ConnectToServer() const
{
	auto connectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server
	connectSocket = socket(_addrInfo.ai_family, _addrInfo.ai_socktype, _addrInfo.ai_protocol);

	if (connectSocket == INVALID_SOCKET)
	{
		ThrowWinApiException("Failed to create the socket for connecting to the server");
	}

	// Connect to server
	const int returnCode = connect(connectSocket, _addrInfo.ai_addr, static_cast<int>(_addrInfo.ai_addrlen));

	if (returnCode == SOCKET_ERROR)
	{
		closesocket(connectSocket);
		return INVALID_SOCKET;
	}

	return connectSocket;
}
