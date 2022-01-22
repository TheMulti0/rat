#include "Connection.h"
#include "Trace.h"

#include <WS2tcpip.h>

Connection::Connection(SOCKET& s) {
	_socket = s;
}

int Connection::Send(const char* buffer, int length) {
	int result = send(_socket, buffer, length, 0);

	if (result == SOCKET_ERROR) {
		Trace("send failed with error: %d\n", WSAGetLastError());
		closesocket(_socket);
		throw std::exception();
	}

	return result;
}

void Connection::Receive(char* buffer, int length) {
	int result;

	do {
		result = recv(_socket, buffer, length, 0);

		if (result > 0)
		{
			Trace("Bytes received: %d\n", result);
			Trace("Received: %s", buffer);
		}
		else if (result == 0)
		{
			Trace("Connection closed\n");
		}
		else
		{
			Trace("recv failed with error: %d\n", WSAGetLastError());
		}

	} while (result > 0);
}

void Connection::Shutdown() {
	int returnCode = shutdown(_socket, SD_SEND);

	if (returnCode == SOCKET_ERROR) {
		Trace("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(_socket);
		throw std::exception();
	}
}