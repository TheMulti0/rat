#pragma once

#include "Trace.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

class AddressInfo
{
public:

	AddressInfo(const char* ip, int port) :
		_addressInfo(ResolveAddressInfo(ip, port))
	{
	}

	~AddressInfo()
	{
		freeaddrinfo(_addressInfo);
	}

	addrinfo& get() {
		return *_addressInfo;
	}

private:

	static addrinfo* ResolveAddressInfo(const char* ip, int port)
	{
		addrinfo* result{};

		addrinfo addrinfo = CreateAddressInfoHints();

		int returnCode = getaddrinfo(
				ip,
				std::to_string(port).c_str(),
				&addrinfo,
				&result);

		if (returnCode != 0)
		{
			Trace("getaddrinfo failed with error: %d\n", returnCode);
			throw std::runtime_error("getaddrinfo failed with error");
		}

		return result;
	}

	static addrinfo CreateAddressInfoHints()
	{
		addrinfo hints;
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		return hints;
	}

	addrinfo* _addressInfo{};
};
