#include "Rat.h"

#include "MessageListener.h"
#include "MessageSender.h"
#include "WinSockConnectionFactory.h"
#include "WinSockConnectionListener.h"

std::unique_ptr<IConnectionFactory> Rat::CreateWinSockConnectionFactory(
	const char* ip, int port)
{
	return std::make_unique<WinSockConnectionFactory>(ip, port);
}

std::unique_ptr<IMessageSender> Rat::CreateMessageSender(IConnection* connection)
{
	return std::make_unique<MessageSender>(connection);
}

std::unique_ptr<IConnectionListener> Rat::CreateWinSockConnectionListener(int port)
{
	return std::make_unique<WinSockConnectionListener>(port);
}

std::unique_ptr<IMessageListener> Rat::CreateMessageListener(
	IConnection* connection,
	std::function<void(MessageType, std::span<char>)> onMessage)
{
	return std::make_unique<MessageListener>(connection, onMessage);
}

std::unique_ptr<IRat> CreateRat()
{
	return std::make_unique<Rat>();
}
