#include "MessageQueue.h"

MessageQueue::MessageQueue(): _sendThread(
	MakeThreadGuard(
		std::thread(&MessageQueue::HandleMessages, this)))
{
}

void MessageQueue::Add(const SendMessage& s)
{
	std::lock_guard guard(_accessMessagesLock);

	_messages.push(s);
	_cv.notify_one();
}

void MessageQueue::HandleMessages()
{
	while (true)
	{
		std::unique_lock guard(_waitForMessagesLock);

		_cv.wait(
			guard,
			[this] { return !_messages.empty(); });

		Send();
	}

}

void MessageQueue::Send()
{
	std::lock_guard guard(_accessMessagesLock);

	while (!_messages.empty())
	{
		SendMessage function = _messages.front();
		function();

		_messages.pop();
	}
}
