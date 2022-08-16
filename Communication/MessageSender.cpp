#include "MessageSender.h"

#include <stdexcept>
#include <utility>

#include "Message.h"
#include "Serializer.h"

MessageSender::MessageSender(IConnection* connection) :
	_connection(connection),
	_queue(CreateOperationQueue())
{
}

void MessageSender::Send(const MessageType type, const SharedSpan content)
{
	_queue->Add(
		[=]
		{
			const int result = SendAll(CreateMessage(type, content));

			if ( result < 0)
			{
				throw std::runtime_error(std::to_string(result));
			}
		});
}

SharedSpan MessageSender::CreateMessage(const MessageType type, SharedSpan content)
{
	auto messageC = Message(type, std::move(content));

	const SharedSpan body = messageC.Serialize();

	const auto length = body.size();

	Serializer s(length + sizeof length);
	s.Add(reinterpret_cast<const char*>(&length), sizeof length);
	s.Add(body);

	return s.Data();
}

int MessageSender::SendAll(SharedSpan buffer) const
{
	auto bytesSent = 0;

	while (bytesSent < buffer.size())
	{
		bytesSent += _connection->Send(
			buffer.begin() + bytesSent,
			buffer.size() - bytesSent);
	}

	return bytesSent;
}
