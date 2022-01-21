#pragma once

#include "Trace.h"
#include "Config.h"
#include "AddressInfo.h"
#include "Connection.h"

//#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

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