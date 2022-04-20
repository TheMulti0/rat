#pragma once

#include <memory>
#include <thread>

#include "IConnection.h"
#include "ThreadGuard.h"

class WinSockHarness
{
public:
	WinSockHarness(
		std::unique_ptr<IConnection> client,
		std::unique_ptr<IConnection> server,
		std::unique_ptr<ThreadGuard> serverThread);

	IConnection* GetClient() const;

	IConnection* GetServer() const;

private:
	std::unique_ptr<IConnection> _client;
	std::unique_ptr<IConnection> _server;
	std::unique_ptr<ThreadGuard> _serverThread;
};

