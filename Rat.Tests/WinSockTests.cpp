#include <mutex>
#include <thread>

#include "GoogleTest.h"
#include "WinSockHarness.h"
#include "WinSock/ConnectionFactory.h"
#include "WinSock/ConnectionListener.h"
#include "WinSock/Initializer.h"

WinSockHarness CreateHarness()
{
	const auto listener = std::make_unique<ConnectionListener>(1234);

	std::mutex mutex;
	std::condition_variable cv;

	std::unique_ptr<IConnection> serverConnection = nullptr;
	const auto serverThread = new std::thread([&]()
		{
			std::unique_lock guard(mutex);
			serverConnection = listener->WaitForConnection();
			cv.notify_all();
		});

	const auto factory = std::make_unique<ConnectionFactory>("localhost", 1234);
	auto connection = factory->Connect();

	std::unique_lock guard(mutex);
	cv.wait(guard, [&]() { return serverConnection != nullptr; });

	auto winSockHarness = WinSockHarness(
		std::move(connection),
		std::move(serverConnection),
		std::make_unique<ThreadGuard>(*serverThread)
	);
	return winSockHarness;
}

void TestMessage(IConnection* sender, IConnection* receiver, const int messageLength)
{
	const auto content = new char[messageLength];
	for (int i = 0; i < messageLength; i++)
	{
		content[i] = static_cast<char>(i);
	}

	EXPECT_EQ(sender->Send(content, messageLength), messageLength);

	char* received = new char[messageLength];
	EXPECT_EQ(receiver->Receive(received, messageLength), messageLength);

	EXPECT_ARRAY_EQ(char, received, content, messageLength);
}

TEST(WinSockTests, TestShortMessage)
{
 	Initializer initializer;
    auto harness = CreateHarness();
	TestMessage(harness.GetClient(), harness.GetServer(), 1);
	TestMessage(harness.GetServer(), harness.GetClient(), 1);
}
