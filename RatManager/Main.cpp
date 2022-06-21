#include <iostream>
#include <memory>
#include <mutex>

#include "RatManager.h"
#include "Trace.h"


int main() {
	const auto rat = CreateFactory();

	std::mutex mutex;
	std::condition_variable cv;

	auto manager = RatManager(
		rat.get(),
		rat->CreateWinSockConnectionListener(4444));

	while (true)
	{
		std::string input;
		std::getline(std::cin, input);

		int pos = input.find(' ');

		std::string command = input.substr(0, pos);
		std::string args = input.substr(pos + 1);

		if (command == "c")
		{
			pos = args.find(' ');

			auto str = args.substr(0, pos);
			const int client = std::stoi(str);
			std::string message = args.substr(pos + 1);

			manager.Send(
				client,
				MessageType::Chat,
				std::span(const_cast<char*>(
					message.c_str()), 
					message.size()));

		} else
		{
			int i = 0;
			for (const auto& clientPipe : manager.GetClients())
			{
				Trace("Client %d: %s\n", i, clientPipe->GetConnection()->GetAddress().c_str());
				i++;
			}
		}

		Trace("\n> ");

		
	}
	

	return 0;
}
