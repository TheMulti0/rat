#include "ISingleProcessManager.h"

#include "SingleProcessManager.h"

std::unique_ptr<ISingleProcessManager> CreateSingleProcessManager(
	std::function<void(std::string)> onMessage,
    const bool inheritHandles, 
	const bool waitForExit)
{
	return std::make_unique<SingleProcessManager>(onMessage, inheritHandles, waitForExit);
}
