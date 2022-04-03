#pragma once

#include <memory>

#include "IConnection.h"
#include "IConnectionListener.h"
#include "WinSockAddressInfo.h"

class WinSockConnectionListener : public IConnectionListener
{
public:
	explicit WinSockConnectionListener(int port);
	~WinSockConnectionListener() override;

	std::unique_ptr<IConnection> WaitForConnection() override;

private:
	void Bind() const;
	void Unbind() const;

	SOCKET CreateListenSocket() const;

	void ListenForConnections() const;

	std::unique_ptr<IConnection> AcceptClientConnection() const;

	std::unique_ptr<WinSockAddressInfo> _addressInfo;
	addrinfo& _addrInfo;
	SOCKET _listenSocket;
};

