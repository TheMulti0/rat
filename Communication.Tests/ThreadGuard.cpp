#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread&& input) : _thread(std::move(input))
{
}

ThreadGuard::~ThreadGuard()
{
	if (_thread.joinable()) {
		_thread.join();
	}
}
