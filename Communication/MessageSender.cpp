#include "MessageSender.h"

#include <utility>

#include "Message.h"
#include "Serializer.h"
#include "Trace.h"

MessageSender::MessageSender(IConnection* connection)
	: _connection(connection)
{
}

int MessageSender::Send(const MessageType type, const SharedSpan content)
{
	return SendAll(
		CreateMessage(type, content));
}

SharedSpan MessageSender::CreateMessage(const MessageType type, SharedSpan content)
{
	auto messageC = Message(type, std::move(content));

	const SharedSpan body = messageC.Serialize();

	const auto length = body.Size();

	Serializer s(length + sizeof length);
	s.Add(reinterpret_cast<const char*>(&length), sizeof length);
	s.Add(body);

	return s.Data();
}

int MessageSender::SendAll(SharedSpan buffer) const
{
	auto bytesSent = 0;

	while (bytesSent < buffer.Size())
	{
		bytesSent += _connection->Send(
			buffer.Data() + bytesSent,
			buffer.Size() - bytesSent);
	}

	return bytesSent;
}
