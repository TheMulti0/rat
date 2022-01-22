#pragma once

#include "Trace.h"
#include "Client.h"

void ClientMain() {
	Client client = Client("localhost", DEFAULT_PORT);
	auto connection = client.Connect();

	const char* sendBuffer = "Ping!";

	char receiveBuffer[DEFAULT_BUFLEN];
	int bytesReceived;

	do {
		connection->Send(sendBuffer, strlen(sendBuffer));

		bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

		std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

		Trace("Received %s\n", message.c_str());
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}