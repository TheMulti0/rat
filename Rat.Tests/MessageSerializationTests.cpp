#include "MessageSerializationTests.h"
#include "SharedConnection.h"

MessageSerializationTest::MessageSerializationTest():
	_connection(std::make_unique<SharedConnection>()),
	_rat(CreateRat()),
	_sender(_rat->CreateMessageSender(_connection.get())),
	_listener(_rat->CreateMessageListener(
		_connection.get(),
		[this](auto type, auto content) { OnMessage(type, content); })),
	_latestMessage(nullptr)
{
}

Message MessageSerializationTest::GetLatestDeserializedMessage()
{
	std::unique_lock guard(_mutex);

	_cv.wait(
		guard,
		[&] { return _latestMessage != nullptr; });

	return *_latestMessage;
}

void MessageSerializationTest::TestMessageSerialization(const size_t contentLength)
{
	constexpr auto type = MessageType::Chat;

	const auto content = std::unique_ptr<char>(new char[contentLength]);
	std::fill_n(content.get(), contentLength, 1);

	int sent = Send(type, content.get(), contentLength);

	const auto deserialized = GetLatestDeserializedMessage();

	EXPECT_EQ(
		deserialized.GetType(),
		type);
	EXPECT_EQ(
		deserialized.GetContent().size(),
		contentLength);
	EXPECT_ARRAY_EQ(
		char,
		deserialized.GetContent().data(),
		content.get(),
		contentLength);
}

void MessageSerializationTest::OnMessage(const MessageType type, const std::span<char> content)
{
	std::unique_lock guard(_mutex);

	_latestMessage = std::make_unique<Message>(Message(type, content));

	_cv.notify_all();
}

int MessageSerializationTest::Send(const MessageType type, char* content, const size_t contentLength) const
{
	return _sender->Send(
		type, 
		std::span(content, contentLength));
}

TEST_F(MessageSerializationTest, TestShortMessage)
{
	TestMessageSerialization(2);
}

TEST_F(MessageSerializationTest, TestLongMessage)
{
	TestMessageSerialization(2048);
}