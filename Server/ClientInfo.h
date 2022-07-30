#pragma once

class ClientInfo
{
public:
	ClientInfo(): Address{}
	{
	}

	ClientInfo(const ClientInfo& info) : Address{ *info.Address }
	{
	}

	ClientInfo& operator=(const ClientInfo& info)
	{
		std::ranges::copy(info.Address, std::begin(Address));
		
		return *this;
	}
	char Address[16];
};
