#pragma once
#include <mutex>

#include "IConnection.h"
#include "IRat.h"
#include "ThreadGuard.h"

class WinSockTestSuite
{
public:
	WinSockTestSuite();

	[[nodiscard]] IConnection* GetClient() const;

	IConnection* GetServer();

private:
	void WaitForServerConnection();

	void RunServer();

	std::unique_ptr<IRat> _rat;
	std::unique_ptr<IConnectionFactory> _factory;
	std::unique_ptr<IConnectionListener> _listener;

	std::unique_ptr<IConnection> _server;

	std::mutex _mutex;
	std::condition_variable _cv;
	std::unique_ptr<ThreadGuard> _serverThread;

	std::unique_ptr<IConnection> _client;
};
