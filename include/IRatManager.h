#pragma once

#include <memory>
#include <span>
#include <vector>

#include "ICommunicationFactory.h"
#include "MessageType.h"

#include <iterator>

#include "SharedSpan.h"

class ClientInfo
{
public:
	ClientInfo() : Address{}
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


class IRatManager
{
public:
	virtual ~IRatManager() = default;

	[[nodiscard]] virtual int GetClientCount() const = 0;

	[[nodiscard]] virtual ClientInfo* GetClients() = 0;

	virtual void Send(int client, MessageType type, SharedSpan content) = 0;

	virtual void Join() = 0;
};

__declspec(dllexport)
std::unique_ptr<IRatManager> CreateRatManager(
	ICommunicationFactory* factory,
	std::unique_ptr<IConnectionListener> server);