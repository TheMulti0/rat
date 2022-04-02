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

int WinSockConnection::Send(const char* buffer, const int length)
{
	int bytesSent = 0;

	while (bytesSent < length)
	{
		const int result = send(
			_socket, 
			buffer + bytesSent, 
			length - bytesSent,
			0);

		if (result == SOCKET_ERROR)
		{
			CloseSocket();
			throw std::runtime_error(Format("send failed with error: %d", WSAGetLastError()));
		}

		bytesSent += result;
	}

	return bytesSent;
}

int WinSockConnection::Receive(char* buffer, const int length)
{
	const int result = recv(
		_socket, 
		buffer, 
		length, 
		0);

	if (result == SOCKET_ERROR)
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