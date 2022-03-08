#pragma once

#include "../shared/Connection.h"
#include "../shared/AddressInfo.h"

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
