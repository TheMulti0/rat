#include "MessageSender.h"

#include "Message.h"

MessageSender::MessageSender(IConnection* connection)
	: _connection(connection)
{
}

bool MessageSender::Send(const MessageType type, const std::span<char> content)
{
	const auto messageC = Message(type, content);
	const std::span<char> serialized = messageC.Serialize();
	const auto data = serialized.data();

	const auto length = serialized.size();
	const int bytesSent = SendAll(
		data,
		length);

	return bytesSent <= 0 || bytesSent < length
		? false
		: true;
}

int MessageSender::SendAll(const char* buffer, const int length) const
{
	int bytesSent = 0;

	while (bytesSent < length)
	{
		bytesSent += _connection->Send(
			buffer + bytesSent,
			length - bytesSent);
	}

	return bytesSent;
}
