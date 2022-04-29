#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread&& input) : _thread(std::move(input))
{
}

void ThreadGuard::Join()
{
	if (_thread.joinable()) {
		_thread.join();
	}
}

ThreadGuard::~ThreadGuard()
{
	Join();
}
