#include <iostream>

#include "Trace.h"
#include "IInitializer.h"
#include "Client.h"
#include "IMessageSender.h"
#include "MessageType.h"

int main() {
	std::unique_ptr<IInitializer> initializer = InitializeWinSock();

	const auto client = Client("localhost", DEFAULT_PORT);
	const auto connection = client.Connect();
	const auto sender = CreateMessageSender(connection.get());

	do {
		Trace("\nCLIENT: Enter something to send: ");
		std::string sendBuffer;
		std::cin >> sendBuffer;
		Trace("\n");

		sender->Send(MessageType::Chat, sendBuffer);

		Trace("CLIENT: Sent %s\n", sendBuffer.c_str());
	}
	while (true);
	connection->Shutdown();

	return 0;
}
