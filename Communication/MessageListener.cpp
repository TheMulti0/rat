#include <memory>
#include <iostream>

#include "MessageListener.h"

MessageListener::MessageListener(
	IConnection* connection,
	std::function<void(MessageType, std::span<char>)> onMessage,
	std::function<void()> onDisconnection
) :
	_connection(connection),
	_onMessage(std::move(onMessage)),
	_onDisconnection(std::move(onDisconnection)),
	_isTerminationRequested(false),
	_thread(std::make_unique<ThreadGuard>(
		std::thread(& MessageListener::Listen, this)))
{
}

MessageListener::~MessageListener()
{
	_isTerminationRequested = true;
}

void MessageListener::Join()
{
	_thread->Join();
}

void MessageListener::Listen() const
{
	while (!_isTerminationRequested)
	{
		const std::unique_ptr<Message> messagePtr = ReceiveMessage();

		if (messagePtr == nullptr)
		{
			_onDisconnection();
			break;
		}

		_onMessage(
			messagePtr->GetType(),
			messagePtr->GetContent());
	}
}

std::unique_ptr<Message> MessageListener::ReceiveMessage() const
{
	const int length = ReceiveMessageLength();
	if (length < 0)
	{
		return nullptr;
	}

	const auto buffer = new char[length];

	const int bytesReceived = ReceiveAll(buffer, length);
	if (bytesReceived < 0 || bytesReceived < length)
	{
		return nullptr;
	}

	auto deserialized = Message::Deserialize(std::span(buffer, length));

	return std::make_unique<Message>(deserialized);
}

int MessageListener::ReceiveMessageLength() const
{
	int length = 0;

	const auto buffer = new char[sizeof length];

	if (const int result = ReceiveAll(buffer, sizeof length) < 0)
	{
		return result;
	}

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

		if (result < 0)
		{
			return result;
		}

		bytesReceived += result;
	}

	return bytesReceived;
}