#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread& thread) : _thread(thread)
{}

ThreadGuard::~ThreadGuard()
{
	if (_thread.joinable())
	{
		_thread.join();
	}
}
