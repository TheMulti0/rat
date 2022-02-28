#pragma once

#include "../shared/AddressInfo.h"
#include "../shared/Connection.h"

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