#include <memory>

#include "MessageListener.h"

MessageListener::MessageListener(
	IConnection* connection,
	std::function<void(MessageType, std::span<char>)> onMessage
) :
	_connection(connection),
	_onMessage(std::move(onMessage)),
	_isTerminationRequested(false),
	_thread(&MessageListener::Listen, this)
{
}

MessageListener::~MessageListener()
{
	_isTerminationRequested = true;

	Join();
}

void MessageListener::Join()
{
	if (_thread.joinable()) {
		_thread.join();
	}
}

void MessageListener::Listen() const
{
	while (!_isTerminationRequested)
	{
		try
		{
			const std::unique_ptr<Message> messagePtr = ReceiveMessage();

			_onMessage(
				messagePtr->GetType(),
				messagePtr->GetContent());
		}
		catch([[maybe_unused]] std::runtime_error& e) 
		{
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
		const int result = _connection->Receive(
			buffer + bytesReceived,
			length - bytesReceived);

		bytesReceived += result;
	}

	return bytesReceived;
}

std::unique_ptr<Message> MessageListener::ReceiveMessage() const
{
	const int length = ReceiveMessageLength();
	const auto buffer = new char[length];

	const int bytesReceived = ReceiveAll(buffer, length);

	if (bytesReceived < 0 || bytesReceived < length)
	{
		return nullptr;
	}

	auto deserialized = Message::Deserialize(std::span(buffer, length));

	return std::make_unique<Message>(deserialized);
}