#include <memory>

#include "RatManager.h"


int main() {
	const auto rat = CreateFactory();

	std::mutex mutex;
	std::condition_variable cv;

	auto manager = RatManager(
		rat.get(),
		rat->CreateWinSockConnectionListener(4444));

	auto lock = std::unique_lock(mutex);
	cv.wait(lock, [&] { return manager.GetClientCount() > 0; });

	manager.Join();

	return 0;
}
