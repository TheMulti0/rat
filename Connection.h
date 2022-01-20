#pragma once

//#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

class Connection {
public:
	Connection(SOCKET& s);

	int Send(const char* buffer, int length);

	void Receive(char* buffer, int length);

	void Shutdown();

private:
	SOCKET _socket;
};

Connection::Connection(SOCKET& s) {
	_socket = s;
}

int Connection::Send(const char* buffer, int length) {
	int result = send(_socket, buffer, length, 0);

	if (result == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
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
			printf("Bytes received: %d\n", result);
			printf("Received: %s", buffer);
		}
		else if (result == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
		}

	} while (result > 0);
}

void Connection::Shutdown() {
	int returnCode = shutdown(_socket, SD_SEND);

	if (returnCode == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(_socket);
		throw std::exception();
	}
}
