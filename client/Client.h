#pragma once

#include "IAddressInfo.h"
#include "IConnection.h"

class Client
{
public:
	Client(const char* ip, int port);

	std::unique_ptr<IConnection> Connect() const;

private:
	SOCKET ConnectToServer() const;

	std::unique_ptr<IAddressInfo> _addressInfo;
	addrinfo& _addrInfo;
};