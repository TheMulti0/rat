#include "ClientPipe.h"

ClientPipe::ClientPipe(std::unique_ptr<IConnection> connection, std::unique_ptr<IMessageSender> sender,
	std::unique_ptr<IMessageListener> listener):
	_connection(std::move(connection)),
	_sender(std::move(sender)),
	_listener(std::move(listener))
{
}

int ClientPipe::Send(MessageType type, std::span<char> content)
{
	return _sender->Send(type, content);
}

void ClientPipe::Join()
{
	_listener->Join();
}
