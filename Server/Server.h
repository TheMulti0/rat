#pragma once

#include <memory>

#include "IConnection.h"
#include "IAddressInfo.h"

class Server
{
public:
	explicit Server(int port);
	~Server();

	std::unique_ptr<IConnection> WaitForConnection() const;

private:
	void Bind() const;
	void Unbind() const;

	SOCKET CreateListenSocket() const;

	void ListenForConnections() const;

	std::unique_ptr<IConnection> AcceptClientConnection() const;

	std::unique_ptr<IAddressInfo> _addressInfo;
	addrinfo& _addrInfo;
	SOCKET _listenSocket;
};

