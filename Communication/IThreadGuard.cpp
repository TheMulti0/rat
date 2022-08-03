#include "IThreadGuard.h"

#include "ThreadGuard.h"

std::unique_ptr<IThreadGuard> MakeThreadGuard(std::thread&& input)
{
	return std::make_unique<ThreadGuard>(
		std::move(input));
}
