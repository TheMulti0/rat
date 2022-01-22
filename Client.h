#pragma once

#include "AddressInfo.h"
#include "Connection.h"

class Client
{
public:
	Client(const char* ip, int port);

	Connection* Connect();

private:
	SOCKET ConnectToServer();

	AddressInfo _addressInfo;
	addrinfo& _addrInfo;
};