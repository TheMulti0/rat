#include <iostream>

#include "Trace.h"
#include "IConnectionFactory.h"
#include "IMessageSender.h"
#include "ICommunicationFactory.h"
#include "MessageType.h"

int main() {
	const auto rat = CreateFactory();

	const auto client = rat->CreateWinSockConnectionFactory("localhost", 4444);
	const auto connection = client->Connect();
	const auto sender = rat->CreateMessageSender(connection.get());

	const auto listener = rat->CreateMessageListener(
		connection.get(),
		[](MessageType type, const std::span<char> content)
		{
			const auto message = std::string(content.begin(), content.end());
			Trace("CLIENT: Received %s\n", message.c_str());
		});

	do {
		Trace("\nCLIENT: Enter something to send: ");
		std::string sendBuffer;
		std::getline(std::cin, sendBuffer);

		/*const auto now = std::chrono::system_clock::now();
		const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
			now.time_since_epoch())
		.count();*/

		sender->Send(MessageType::Chat, sendBuffer);
	}
	while (true);
	connection->Shutdown();

	return 0;
}
