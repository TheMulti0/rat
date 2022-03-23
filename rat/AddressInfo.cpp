#include <stdexcept>
#include <string>
#include <WS2tcpip.h>

#include "AddressInfo.h"
#include "Format.h"

AddressInfo::AddressInfo(const char* ip, const int port) :
	_addressInfo(ResolveAddressInfo(ip, port))
{
}

AddressInfo::~AddressInfo()
{
	freeaddrinfo(_addressInfo);
}

addrinfo& AddressInfo::Get()
{
	return *_addressInfo;
}

addrinfo* AddressInfo::ResolveAddressInfo(const char* ip, int port)
{
	addrinfo* result{};

	const addrinfo addrinfo = CreateAddressInfoHints();

	const int returnCode = getaddrinfo(
		ip,
		std::to_string(port).c_str(),
		&addrinfo,
		&result);

	if (returnCode != 0)
	{
		throw std::runtime_error(Format("getaddrinfo failed with error: %d", returnCode));
	}

	return result;
}

addrinfo AddressInfo::CreateAddressInfoHints()
{
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	return hints;
}

std::unique_ptr<IAddressInfo> CreateAddressInfo(const char* ip, int port)
{
	return std::make_unique<AddressInfo>(ip, port);
}