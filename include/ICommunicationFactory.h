#pragma once

#include <functional>

#include "IConnectionFactory.h"
#include "IConnectionListener.h"
#include "IMessageListener.h"
#include "IMessageSender.h"

class ICommunicationFactory
{
public:
	virtual ~ICommunicationFactory() = default;

	virtual std::unique_ptr<IConnectionFactory> CreateWinSockConnectionFactory(
		const char* ip, int port) = 0;

	virtual std::unique_ptr<IMessageSender> CreateMessageSender(
		IConnection* connection) = 0;

	virtual std::unique_ptr<IConnectionListener> CreateWinSockConnectionListener(
		int port) = 0;

	virtual std::unique_ptr<IMessageListener> CreateMessageListener(
		IConnection* connection,
		OnMessage onMessage,
		OnDisconnection onDisconnection) = 0;
};

__declspec(dllexport)
std::unique_ptr<ICommunicationFactory> CreateFactory();