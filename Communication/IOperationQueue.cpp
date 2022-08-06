#include "IOperationQueue.h"

#include "OperationQueue.h"

std::unique_ptr<IOperationQueue> CreateOperationQueue()
{
	return std::make_unique<OperationQueue>();
}
