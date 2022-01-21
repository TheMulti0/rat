#pragma once

#include "Trace.h"
#include "Connection.h"
#include "Config.h"
#include "AddressInfo.h"

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

class Server
{
public:
	Server(int port);
	~Server();

	Connection* WaitForConnection();

private:
	void Bind();
	void Unbind();

	SOCKET CreateListenSocket();

	void ListenForConnections();

	Connection* AcceptClientConnection();

	AddressInfo _addressInfo;
	addrinfo& _addrInfo;
	SOCKET _listenSocket;
};

