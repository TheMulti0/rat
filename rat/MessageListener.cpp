#include "MessageListener.h"

#include "IInitializer.h"

MessageListener::MessageListener(
	IConnection* connection,
	void (*onMessage)(MessageType, std::string)
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

	const auto buffer = new char[sizeof length];
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
	const auto buffer = new char[length + 1];
	buffer[length] = '\0';

	int bytesReceived = ReceiveAll(buffer, length);

	if (bytesReceived <= 0 || bytesReceived < length) 
	{
		return nullptr;
	}

	auto deserialized = Message::Deserialize(buffer);
	delete[] buffer;

	return std::make_unique<Message>(deserialized);
}

std::unique_ptr<IMessageListener> CreateMessageListener(
	IConnection* connection,
	void (*onMessage)(MessageType, std::string))
{
	return std::make_unique<MessageListener>(connection, onMessage);
}
