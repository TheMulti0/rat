#include <memory>
#include <iostream>

#include "MessageListener.h"

MessageListener::MessageListener(
	IConnection* connection,
	OnMessage onMessage,
	OnDisconnection onDisconnection
) :
	_connection(connection),
	_onMessage(std::move(onMessage)),
	_onDisconnection(std::move(onDisconnection)),
	_isTerminationRequested(false),
	_thread(MakeThreadGuard(
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

	auto buffer = SharedSpan(length);

	const int bytesReceived = ReceiveAll(buffer.Data(), length);
	if (bytesReceived < 0 || bytesReceived < length)
	{
		return nullptr;
	}
	auto deserialized = Message::Deserialize(buffer);

	return std::make_unique<Message>(deserialized);
}

int MessageListener::ReceiveMessageLength() const
{
	int length = 0;

	const auto buffer = std::make_unique<char[]>(sizeof length);

	if (const int result = ReceiveAll(buffer.get(), sizeof length) < 0)
	{
		return result;
	}

	length = *reinterpret_cast<int*>(buffer.get());

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