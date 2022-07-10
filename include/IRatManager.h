#pragma once

#include <memory>
#include <span>
#include <vector>

#include "IClientPipe.h"
#include "ICommunicationFactory.h"
#include "MessageType.h"

class IRatManager
{
public:
	virtual ~IRatManager() = default;

	[[nodiscard]] virtual int GetClientCount() const = 0;

	virtual std::vector<std::shared_ptr<IClientPipe>> GetClients() = 0;

	[[nodiscard]] virtual int Send(int client, MessageType type, std::span<char> content) const = 0;

	virtual void Join() = 0;
};

__declspec(dllexport)
std::unique_ptr<IRatManager> CreateRatManager(
	ICommunicationFactory* factory,
	std::unique_ptr<IConnectionListener> server);