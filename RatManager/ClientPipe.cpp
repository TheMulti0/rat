#include "ClientPipe.h"

ClientPipe::ClientPipe(std::unique_ptr<IConnection> connection, std::unique_ptr<IMessageSender> sender,
	std::unique_ptr<IMessageListener> listener):
	_connection(std::move(connection)),
	_sender(std::move(sender)),
	_listener(std::move(listener))
{
}

IConnection* ClientPipe::GetConnection() const
{
	return _connection.get();
}

IMessageSender* ClientPipe::GetSender() const
{
	return _sender.get();
}

IMessageListener* ClientPipe::GetListener() const
{
	return _listener.get();
}

