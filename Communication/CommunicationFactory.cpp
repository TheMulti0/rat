#include "CommunicationFactory.h"

#include "MessageListener.h"
#include "MessageSender.h"
#include "WinSock/ConnectionFactory.h"
#include "WinSock/ConnectionListener.h"

std::unique_ptr<IConnectionFactory> CommunicationFactory::CreateWinSockConnectionFactory(
	const char* ip, int port)
{
	return std::make_unique<ConnectionFactory>(ip, port);
}

std::unique_ptr<IMessageSender> CommunicationFactory::CreateMessageSender(IConnection* connection)
{
	return std::make_unique<MessageSender>(connection);
}

std::unique_ptr<IConnectionListener> CommunicationFactory::CreateWinSockConnectionListener(int port)
{
	return std::make_unique<ConnectionListener>(port);
}

std::unique_ptr<IMessageListener> CommunicationFactory::CreateMessageListener(
	IConnection* connection,
	OnMessage onMessage,
	OnDisconnection onDisconnection)
{
	return std::make_unique<MessageListener>(connection, onMessage, onDisconnection);
}

std::unique_ptr<ICommunicationFactory> CreateFactory()
{
	return std::make_unique<CommunicationFactory>();
}
