#pragma once

#include <functional>
#include <mutex>
#include <queue>

#include "IThreadGuard.h"

using SendMessage = std::function<void()>;

class MessageQueue
{
public:
	MessageQueue();

	void Add(const SendMessage& s);

private:
	void HandleMessages();

	void Send();

	std::queue<SendMessage> _messages;
	std::mutex _accessMessagesLock;
	std::mutex _waitForMessagesLock;
	std::condition_variable _cv;
	std::unique_ptr<IThreadGuard> _sendThread;
};
