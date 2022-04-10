#include <memory>

#include "MessageListener.h"

MessageListener::MessageListener(
	IConnection* connection,
	std::function<void(MessageType, std::string)> onMessage
) :
	_connection(connection),
	_onMessage(onMessage),
	_thread(&MessageListener::Listen, this)
{
}

MessageListener::~MessageListener()
{
	_thread.join();
}

void MessageListener::Listen() const
{
	while (true)
	{
		const auto messagePtr = ReceiveMessage();

		if (messagePtr != nullptr)
		{
			_onMessage(
				messagePtr->GetType(),
				messagePtr->GetMessageString());
		}
	}
}

int MessageListener::ReceiveMessageLength() const
{
	int length = 0;

	char* buffer = new char[sizeof length];
	ReceiveAll(buffer, sizeof length);

	length = *reinterpret_cast<int*>(buffer);

	return length;
}

int MessageListener::ReceiveAll(char* buffer, const int length) const
{
	int bytesReceived = 0;

	while (bytesReceived < length)
	{
		bytesReceived += _connection->Receive(
			buffer + bytesReceived,
			length - bytesReceived);
	}

	return bytesReceived;
}

std::unique_ptr<Message> MessageListener::ReceiveMessage() const
{
	const int length = ReceiveMessageLength();
	const auto buffer = new char[length];

	const int bytesReceived = ReceiveAll(buffer, length);

	if (bytesReceived == 0)
	{
		
	}
	if (bytesReceived < 0 || bytesReceived < length)
	{
		return nullptr;
	}

	auto deserialized = Message::Deserialize(std::span<char>(buffer, length));

	return std::make_unique<Message>(deserialized);
}