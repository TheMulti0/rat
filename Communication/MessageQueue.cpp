#include "MessageQueue.h"

MessageQueue::MessageQueue():
	_sendThread(
		MakeThreadGuard(
			std::thread(&MessageQueue::HandleMessages, this))),
	_isTerminationRequested(false)
{
}

MessageQueue::~MessageQueue()
{
	_isTerminationRequested = true;
	_cv.notify_one();
}

void MessageQueue::Add(const SendMessage& s)
{
	std::lock_guard guard(_accessMessagesLock);

	_messages.push(s);
	_cv.notify_one();
}

void MessageQueue::HandleMessages()
{
	while (!_isTerminationRequested)
	{
		Send();

		std::unique_lock guard(_waitForMessagesLock);

		_cv.wait(
			guard,
			[this] { return !_messages.empty() || _isTerminationRequested; });
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
