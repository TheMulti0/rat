#pragma once

class AddressInfo
{
public:
	AddressInfo(const char* ip, int port);

	~AddressInfo();

	addrinfo& Get();

private:
	static addrinfo* ResolveAddressInfo(const char* ip, int port);

	static addrinfo CreateAddressInfoHints();

	addrinfo* _addressInfo{};
};
