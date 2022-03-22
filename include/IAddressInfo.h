#pragma once

#include <memory>
#include <WinSock2.h>

class IAddressInfo
{
public:

	virtual ~IAddressInfo() = default;

	virtual addrinfo& Get() = 0;
};

__declspec(dllexport)
std::unique_ptr<IAddressInfo> CreateAddressInfo(const char* ip, int port);