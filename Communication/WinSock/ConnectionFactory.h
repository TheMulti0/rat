#pragma once

#include <functional>

#include "IConnectionFactory.h"
#include "AddressInfo.h"

class ConnectionFactory : public IConnectionFactory
{
public:
	ConnectionFactory(const char* ip, int port);

	std::unique_ptr<IConnection> Connect() override;

private:
	[[nodiscard]] SOCKET ConnectToServer() const;
	
	std::unique_ptr<AddressInfo> _addressInfo;
	addrinfo& _addrInfo;
};

