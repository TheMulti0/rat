#pragma once

#include <thread>

class ThreadGuard
{
public:
	explicit ThreadGuard(std::thread& thread);

	~ThreadGuard();
	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;
private:
	std::thread& _thread;
};
