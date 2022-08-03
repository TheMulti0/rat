#pragma once

#include <thread>

class IThreadGuard
{
public:
	virtual ~IThreadGuard() = default;

	virtual void Join() = 0;
};

__declspec(dllexport)
std::unique_ptr<IThreadGuard> MakeThreadGuard(std::thread&& input);
