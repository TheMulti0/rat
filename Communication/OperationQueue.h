#pragma once

#include <functional>
#include <mutex>
#include <queue>

#include "IOperationQueue.h"
#include "IThreadGuard.h"

class OperationQueue : public IOperationQueue
{
public:
	OperationQueue();
	~OperationQueue() override;

	void Add(const Operation& s) override;

private:
	void HandleMessages();

	void Send();

	std::queue<Operation> _operations;
	std::mutex _accessOperationsLock;
	std::mutex _waitForOperationsLock;
	std::condition_variable _cv;
	std::unique_ptr<IThreadGuard> _sendThread;
	bool _isTerminationRequested;
};
