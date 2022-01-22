#pragma once

#include "Trace.h"
#include "Client.h"

void ClientMain() {
	Client client = Client("localhost", DEFAULT_PORT);
	auto connection = client.Connect();

	char receiveBuffer[DEFAULT_BUFLEN];
	int bytesReceived;

	do {
		Trace("\nCLIENT: Enter something to send: ");
		std::string sendBuffer;
		std::cin >> sendBuffer;
		Trace("\n");

		connection->Send(sendBuffer.c_str(), sendBuffer.length());

		bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

		std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

		Trace("CLIENT: Received %s\n", message.c_str());
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}