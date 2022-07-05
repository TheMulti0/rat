#pragma once

#include <vector>

#include "ClientPipe.h"
#include "ICommunicationFactory.h"
#include "IConnectionListener.h"
#include "ThreadGuard.h"

class RatManager
{
public:
	explicit RatManager(
		ICommunicationFactory* factory,
		std::unique_ptr<IConnectionListener> server);

	~RatManager();

	[[nodiscard]] int GetClientCount() const;

	std::vector<std::shared_ptr<ClientPipe>> GetClients();

	[[nodiscard]] int Send(int client, MessageType type, std::span<char> content) const;

	void Join();

private:
	void Listen();

	void OnDisconnection(int client);

	static void OnMessage(
		int client,
		MessageType type,
		std::span<char> content);

	ICommunicationFactory* _factory;
	std::unique_ptr<IConnectionListener> _server;
	std::vector<std::shared_ptr<ClientPipe>> _clients;
	std::unique_ptr<ThreadGuard> _listenThread;
	int _clientCount;
	bool _isTerminationRequested;
};

