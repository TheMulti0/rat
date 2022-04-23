#pragma once

#include "GoogleTest.h"
#include "WinSockTestSuite.h"

class WinSockTest : public testing::Test
{
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	void TestMessage(
		bool isClientSender,
		int messageLength) const;

private:
	static std::unique_ptr<char> CreateContent(int messageLength);

	static std::unique_ptr<WinSockTestSuite> _suite;
};
