#pragma once

#include "Trace.h"
#include "Client.h"

void ClientMain() {
	Client client = Client("localhost", DEFAULT_PORT);

	auto connection = client.Connect();

	Trace("client connected\n");

	char recvBuffer[DEFAULT_BUFLEN];
	int recvBufferLen = DEFAULT_BUFLEN;

	while (true) {
		Trace("Enter text to send (type 'cancel' to stop)\n");
		std::string sendBuffer = "hi";
		std::cin >> sendBuffer;

		if (sendBuffer == "cancel") {
			break;
		}

		int sent = connection->Send(sendBuffer.c_str(), sendBuffer.size());
		Trace("Bytes sent: %ld\n", sent);

		// Receive until the peer closes the connection
		connection->Receive(recvBuffer, recvBufferLen);
	}

	connection->Shutdown();
}