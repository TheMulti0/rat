#include "WinSockTestSuite.h"

WinSockTestSuite::WinSockTestSuite():
	_rat(CreateFactory()),
	_factory(_rat->CreateWinSockConnectionFactory("localhost", 1234)),
	_listener(_rat->CreateWinSockConnectionListener(1234)),
	_serverThread(
		std::make_unique<ThreadGuard>(
			std::thread(
				&WinSockTestSuite::RunServer, this))),
	_client(_factory->Connect())
{
	WaitForServerConnection();
}

IConnection* WinSockTestSuite::GetClient() const
{
	return _client.get();
}

IConnection* WinSockTestSuite::GetServer()
{
	std::unique_lock guard(_mutex);

	return _server.get();
}

void WinSockTestSuite::WaitForServerConnection()
{
	std::unique_lock guard(_mutex);

	_cv.wait(
		guard,
		[&] { return _server != nullptr; });
}

void WinSockTestSuite::RunServer()
{
	std::unique_lock guard(_mutex);

	_server = _listener->WaitForConnection();

	_cv.notify_all();
}
