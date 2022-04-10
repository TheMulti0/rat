#pragma once

#include "IRat.h"
#include "WinSockInitializer.h"

class Rat : public IRat
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
		std::function<void(MessageType, std::string)> onMessage) override;

	std::unique_ptr<IMessagesHandler> CreateMessagesHandler(
		IConnection* connection) override;

private:
	WinSockInitializer _initializer;
};