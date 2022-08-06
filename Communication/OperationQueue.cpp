#include "OperationQueue.h"

OperationQueue::OperationQueue():
	_sendThread(
		MakeThreadGuard(
			std::thread(&OperationQueue::HandleMessages, this))),
	_isTerminationRequested(false)
{
}

OperationQueue::~OperationQueue()
{
	_isTerminationRequested = true;
	_cv.notify_one();
}

void OperationQueue::Add(const Operation& s)
{
	std::lock_guard guard(_accessOperationsLock);

	_operations.push(s);
	_cv.notify_one();
}

void OperationQueue::HandleMessages()
{
	while (!_isTerminationRequested)
	{
		Send();

		std::unique_lock guard(_waitForOperationsLock);

		_cv.wait(
			guard,
			[this] { return !_operations.empty() || _isTerminationRequested; });
	}

}

void OperationQueue::Send()
{
	std::lock_guard guard(_accessOperationsLock);

	while (!_operations.empty())
	{
		Operation function = _operations.front();
		function();

		_operations.pop();
	}
}
