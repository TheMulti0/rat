#pragma once

#include <WS2tcpip.h>

class AddressInfo
{
public:
	AddressInfo(const char* ip, int port);

	~AddressInfo();

	addrinfo& Get() const;

private:
	static addrinfo* ResolveAddressInfo(const char* ip, int port);

	static addrinfo CreateAddressInfoHints();

	addrinfo* _addressInfo{};
};
