#pragma once

#include <functional>
#include <memory>

#include "IConnection.h"
#include "IConnectionListener.h"
#include "AddressInfo.h"

class ConnectionListener : public IConnectionListener
{
public:
	explicit ConnectionListener(int port);
	~ConnectionListener() override;

	std::unique_ptr<IConnection> WaitForConnection() override;

private:
	void Bind() const;
	void Unbind() const;

	SOCKET CreateListenSocket() const;

	void ListenForConnections() const;

	std::unique_ptr<IConnection> AcceptClientConnection() const;

	std::unique_ptr<AddressInfo> _addressInfo;
	addrinfo& _addrInfo;
	SOCKET _listenSocket;
};

