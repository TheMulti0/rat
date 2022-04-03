#pragma once

class WinSockAddressInfo
{
public:
	WinSockAddressInfo(const char* ip, int port);

	~WinSockAddressInfo();

	addrinfo& Get();

private:
	static addrinfo* ResolveAddressInfo(const char* ip, int port);

	static addrinfo CreateAddressInfoHints();

	addrinfo* _addressInfo{};
};
