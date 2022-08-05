#pragma once

#include <mutex>

#include "GoogleTest.h"
#include "IConnection.h"
#include "ICommunicationFactory.h"
#include "Message.h"

class MessageSerializationTest : public testing::Test
{
protected:
	MessageSerializationTest();

	Message GetLatestDeserializedMessage();

	void TestMessageSerialization(int contentLength);

private:
	void OnMessage(MessageType type, SharedSpan content);

	void Send(MessageType type, char* content, int contentLength) const;

	std::unique_ptr<IConnection> _connection;
	std::unique_ptr<ICommunicationFactory> _rat;
	std::unique_ptr<IMessageSender> _sender;
	std::unique_ptr<IMessageListener> _listener;

	std::unique_ptr<Message> _latestMessage;
	std::mutex _mutex;
	std::condition_variable _cv;
};
