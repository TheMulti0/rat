#pragma once

#include "IAddressInfo.h"

class AddressInfo : public IAddressInfo
{
public:

	AddressInfo(const char* ip, int port);

	~AddressInfo() override;

	addrinfo& Get() override;

private:

	static addrinfo* ResolveAddressInfo(const char* ip, int port);

	static addrinfo CreateAddressInfoHints();

	addrinfo* _addressInfo{};
};
