#include <WS2tcpip.h>
#include <stdexcept>

#include "Connection.h"
#include "Format.h"

Connection::Connection(const SOCKET& s) :
		_socket(s)
{
}

Connection::~Connection()
{
	CloseSocket();
}

int Connection::Send(const char* buffer, const int length)
{
	const int bytesSent = send(
		_socket,
		buffer,
		length,
		0);

	if (bytesSent == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("send failed with error: %d", WSAGetLastError()));
	}

	return bytesSent;
}

int Connection::Receive(char* buffer, const int length)
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

void Connection::Shutdown()
{
	const int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("shutdown failed with error: %d\n", WSAGetLastError()));
	}
}

void Connection::CloseSocket() const
{
	closesocket(_socket);
}