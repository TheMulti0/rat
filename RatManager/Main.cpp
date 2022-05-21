#include <iostream>
#include <memory>
#include <mutex>

#include "RatManager.h"


int main() {
	const auto rat = CreateFactory();

	std::mutex mutex;
	std::condition_variable cv;

	auto manager = RatManager(
		rat.get(),
		rat->CreateWinSockConnectionListener(4444));

	std::string in;
	std::cin >> in;
	int client = std::stoi(in.substr(0, 1));
	std::string m = in.substr(1);

	manager.Send(client, MessageType::Chat, std::span(const_cast<char*>(m.c_str()), m.size()));

	auto lock = std::unique_lock(mutex);
	cv.wait(lock, [&] { return manager.GetClientCount() > 0; });

	manager.Join();

	return 0;
}
