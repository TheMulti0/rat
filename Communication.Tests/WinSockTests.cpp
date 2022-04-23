#include "WinSockTests.h"

std::unique_ptr<WinSockTestSuite> WinSockTest::_suite;

void WinSockTest::SetUpTestCase()
{
	_suite = std::make_unique<WinSockTestSuite>();
}

void WinSockTest::TearDownTestCase()
{
	_suite->~WinSockTestSuite();
}

void WinSockTest::TestMessage(const bool isClientSender, const int messageLength) const
{
	const auto sender = isClientSender
		? _suite->GetClient()
		: _suite->GetServer();

	const auto receiver = !isClientSender
		? _suite->GetClient()
		: _suite->GetServer();

	const auto content = CreateContent(messageLength);
	EXPECT_EQ(
		sender->Send(content.get(), messageLength),
		messageLength);

	const auto received = std::unique_ptr<char>(new char[messageLength]);
	EXPECT_EQ(
		receiver->Receive(received.get(), messageLength),
		messageLength);

	EXPECT_ARRAY_EQ(
		char,
		received.get(),
		content.get(),
		messageLength);
}

std::unique_ptr<char> WinSockTest::CreateContent(const int messageLength)
{
	const auto content = new char[messageLength];
	for (int i = 0; i < messageLength; i++)
	{
		content[i] = static_cast<char>(i);
	}

	return std::unique_ptr<char>(content);
}

TEST_F(WinSockTest, TestShortMessage)
{
	TestMessage(true, 1);
	TestMessage(false, 1);
}