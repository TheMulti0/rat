#pragma once

#include "ICommunicationFactory.h"
#include "WinSock/Initializer.h"

class CommunicationFactory : public ICommunicationFactory
{
public:
	std::unique_ptr<IConnectionFactory> CreateWinSockConnectionFactory(
		const char* ip, int port) override;

	std::unique_ptr<IMessageSender> CreateMessageSender(
		IConnection* connection) override;

	std::unique_ptr<IConnectionListener> CreateWinSockConnectionListener(
		int port) override;

	std::unique_ptr<IMessageListener> CreateMessageListener(
		IConnection* connection,
		OnMessage onMessage,
		OnDisconnection onDisconnection) override;

private:
	Initializer _initializer;
};
