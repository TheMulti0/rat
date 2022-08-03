#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread&& input) : _thread(std::move(input))
{
}

void ThreadGuard::Join()
{
	if (_thread.joinable() && _thread.get_id() != std::this_thread::get_id())
	{
		_thread.join();
		return;
	}

	_thread.detach();
}

ThreadGuard::~ThreadGuard()
{
	Join();
}
