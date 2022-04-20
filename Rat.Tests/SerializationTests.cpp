#include <span>

#include "GoogleTest.h"
#include "MessageType.h"

void TestMessageSerialization(const int contentLength)
{
	const auto content = new char[contentLength];
	for (int i = 0; i < contentLength; i++)
	{
		content[i] = static_cast<char>(i);
	}

	const auto message = Message(
		MessageType::Chat, std::span(content, contentLength));

	const auto deserialized = Message::Deserialize(message.Serialize());

	MessageEquals(deserialized, message);
}

TEST(SerializationTests, TestShortMessage)
{
	TestMessageSerialization(2);
}

TEST(SerializationTests, TestLongMessage)
{
	TestMessageSerialization(2048);
}