#pragma once

#include <functional>

using Operation = std::function<void()>;

class IOperationQueue
{
public:
	virtual ~IOperationQueue() = default;

	virtual void Add(const Operation& operation) = 0;
};

__declspec(dllexport)
std::unique_ptr<IOperationQueue> CreateOperationQueue();