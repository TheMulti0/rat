#include "Connection.h"
#include "Trace.h"

#include <WS2tcpip.h>

Connection::Connection(SOCKET& s) :
		_socket(s)
{
}

Connection::~Connection() {
	closesocket(_socket);
}

int Connection::Send(const char* buffer, int length)
{
	int result = send(_socket, buffer, length, 0);

	if (result == SOCKET_ERROR)
	{
		Trace("send failed with error: %d\n", WSAGetLastError());
		closesocket(_socket);
		throw std::exception();
	}

	return result;
}

int Connection::Receive(char* buffer, int length)
{
	int result = recv(_socket, buffer, length, 0);

	if (result < 0)
	{
		Trace("recv failed with error: %d\n", WSAGetLastError());
	}

	return result;
}

void Connection::Shutdown()
{
	int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		Trace("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(_socket);
		throw std::exception();
	}
}