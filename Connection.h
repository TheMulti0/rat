#pragma once

#include <WinSock2.h>

class Connection {
public:
	Connection(SOCKET& s);

	int Send(const char* buffer, int length);

	void Receive(char* buffer, int length);

	void Shutdown();

private:
	SOCKET _socket;
};