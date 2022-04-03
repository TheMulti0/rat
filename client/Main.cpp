#include <iostream>

#include "Trace.h"
#include "IConnectionFactory.h"
#include "IMessageSender.h"
#include "IRat.h"
#include "MessageType.h"

int main() {
	const auto rat = CreateRat();

	const auto client = rat->CreateWinSockConnectionFactory("localhost", 4444);
	const auto connection = client->Connect();
	const auto sender = rat->CreateMessageSender(connection.get());

	do {
		Trace("\nCLIENT: Enter something to send: ");
		std::string sendBuffer;
		std::getline(std::cin, sendBuffer);

		sender->Send(MessageType::Chat, sendBuffer);
	}
	while (true);
	connection->Shutdown();

	return 0;
}
