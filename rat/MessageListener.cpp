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

std::unique_ptr<Message> MessageListener::ReceiveMessage() const
{
	size_t length;
	char* buffer = new char[sizeof length];
	int j = _connection->Receive(buffer, sizeof length);
	length = *reinterpret_cast<int*>(buffer);
	buffer = new char[length + 1];
	buffer[length] = '\0';

	int bytesReceived = 0;
	while (bytesReceived < length)
	{
		bytesReceived += _connection->Receive(
			buffer + bytesReceived,
			length - bytesReceived);
	}

	if (bytesReceived <= 0) return nullptr;

	auto deserialize = Message::Deserialize(buffer);
	delete[] buffer;

	return std::make_unique<Message>(deserialize);
}

std::unique_ptr<IMessageListener> CreateMessageListener(
	IConnection* connection,
	void (*onMessage)(MessageType, std::string))
{
	return std::make_unique<MessageListener>(connection, onMessage);
}
