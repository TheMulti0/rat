#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread&& input) : _thread(std::move(input))
{
}

void ThreadGuard::Join()
{
	if (!_thread.joinable()) {
		return;
	}

	if (_thread.get_id() == std::this_thread::get_id())
	{
		_thread.detach();
	}
	else
	{
		_thread.join();
	}
}

ThreadGuard::~ThreadGuard()
{
	Join();
}
