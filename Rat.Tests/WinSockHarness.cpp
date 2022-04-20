#include "WinSockHarness.h"

WinSockHarness::WinSockHarness(
	std::unique_ptr<IConnection> client, 
	std::unique_ptr<IConnection> server,
	std::unique_ptr<ThreadGuard> serverThread) :
	_client(std::move(client)),
	_server(std::move(server)),
	_serverThread(std::move(serverThread))
{
}

IConnection* WinSockHarness::GetClient() const
{
	return _client.get();
}

IConnection* WinSockHarness::GetServer() const
{
	return _server.get();
}
