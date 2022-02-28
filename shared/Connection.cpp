#include "Connection.h"
#include "Format.h"

#include <WS2tcpip.h>
#include <stdexcept>

Connection::Connection(SOCKET& s) :
		_socket(s)
{
}

Connection::~Connection() {
	CloseSocket();
}

int Connection::Send(const char* buffer, int length)
{
	int result = send(_socket, buffer, length, 0);

	if (result == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("send failed with error: %d", WSAGetLastError()));
	}

	return result;
}

int Connection::Receive(char* buffer, int length)
{
	int result = recv(_socket, buffer, length, 0);

	if (result < 0)
	{
		CloseSocket();
		throw std::runtime_error(Format("recv failed with error: %d", WSAGetLastError()));
	}

	return result;
}

void Connection::Shutdown()
{
	int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		CloseSocket();
		throw std::runtime_error(Format("shutdown failed with error: %d\n", WSAGetLastError()));
	}
}

void Connection::CloseSocket()
{
	closesocket(_socket);
}
