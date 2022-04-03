#pragma once

#include "IConnectionFactory.h"
#include "WinSockAddressInfo.h"

class WinSockConnectionFactory : public IConnectionFactory
{
public:
	WinSockConnectionFactory(const char* ip, int port);

	std::unique_ptr<IConnection> Connect() override;

private:
	SOCKET ConnectToServer() const;
	
	std::unique_ptr<WinSockAddressInfo> _addressInfo;
	addrinfo& _addrInfo;

};

