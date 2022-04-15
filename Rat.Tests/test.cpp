#include "pch.h"

#include <span>

#include "Message.h"
#include "MessageType.h"

void MessageEquals(Message lhs, Message rhs)
{
	EXPECT_EQ(
		lhs.GetType(),
		lhs.GetType());
	EXPECT_ARRAY_EQ(
		char,
		lhs.GetContent().data(),
		rhs.GetContent().data(),
		lhs.GetContent().size());
}

TEST(MessageSerializeTests, TestAb)
{
	constexpr int contentLength = 2;
	auto content = new char[] { 'a', 'b' };

	auto message = Message(
		MessageType::Chat, std::span(content, contentLength));

	const auto deserialized = Message::Deserialize(message.Serialize());

	MessageEquals(deserialized, message);
}