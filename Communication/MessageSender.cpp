#include "MessageSender.h"

#include "Message.h"
#include "Serializer.h"

MessageSender::MessageSender(IConnection* connection)
	: _connection(connection)
{
}

int MessageSender::Send(const MessageType type, const std::span<char> content)
{
	const auto message = CreateMessage(type, content);

	return SendAll(
		message.data(),
		message.size());
}

std::span<char> MessageSender::CreateMessage(const MessageType type, const std::span<char> content)
{
	const auto messageC = Message(type, content);
	const std::span<char> body = messageC.Serialize();
	const auto data = body.data();
	const int length = body.size();

	Serializer s(length + sizeof length);
	s.Add(reinterpret_cast<const char*>(&length), sizeof length);
	s.Add(body);

	return s.Data();
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
