#include <WS2tcpip.h>
#include <stdexcept>

#include "WinSockConnection.h"
#include "Format.h"

WinSockConnection::WinSockConnection(const SOCKET& s) :
		_socket(s)
{
}

WinSockConnection::~WinSockConnection()
{
	CloseSocket();
}

int WinSockConnection::Send(const char* buffer, int length)
{
	const int result = send(_socket, buffer, length, 0);

	if (result == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("send failed with error: %d", WSAGetLastError()));
	}

	return result;
}

int WinSockConnection::Receive(char* buffer, int length)
{
	const int result = recv(_socket, buffer, length, 0);

	if (result < 0)
	{
		CloseSocket();
		throw std::runtime_error(Format("recv failed with error: %d", WSAGetLastError()));
	}

	return result;
}

void WinSockConnection::Shutdown()
{
	const int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("shutdown failed with error: %d\n", WSAGetLastError()));
	}
}

void WinSockConnection::CloseSocket() const
{
	closesocket(_socket);
}