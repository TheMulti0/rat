#include "MessageSender.h"

#include "Message.h"

MessageSender::MessageSender(IConnection* connection)
	: _connection(connection)
{
}

bool MessageSender::Send(const MessageType type, const std::string message)
{
	const auto messageC = Message(type, message);
	const std::span<char> buffer = messageC.Serialize();
	
	const int bytesSent = _connection->Send(
		buffer.data(),
		buffer.size());

	if (bytesSent <= 0) return false;

	return true;
}

std::unique_ptr<IMessageSender> CreateMessageSender(IConnection* connection)
{
	return std::make_unique<MessageSender>(connection);
}