#pragma once

#include "Client.h"

void ClientMain() {
	WinSock winSock;

	Client client = Client("localhost", DEFAULT_PORT);

	auto connection = client.Connect();

	printf("client connected");

	char recvBuffer[DEFAULT_BUFLEN];
	int recvBufferLen = DEFAULT_BUFLEN;

	while (true) {
		printf("Enter text to send (type 'cancel' to stop)");
		std::string sendBuffer;
		std::cin >> sendBuffer;

		if (sendBuffer == "cancel") {
			break;
		}

		int sent = connection->Send(sendBuffer.c_str(), sendBuffer.size());
		printf("Bytes sent: %ld\n", sent);


		// Receive until the peer closes the connection
		connection->Receive(recvBuffer, recvBufferLen);
	}

	connection->Shutdown();
}