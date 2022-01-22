#pragma once

#include "Trace.h"
#include "Server.h"
#include "WinSock.h"

void ServerMain() {
	Server server = Server(DEFAULT_PORT);

	auto connection = server.WaitForConnection();

	const char* sendBuffer = "Pong!";

	char receiveBuffer[DEFAULT_BUFLEN];
	int bytesReceived;

	do {
		bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

		std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

		Trace("Received %s\n", message.c_str());

		connection->Send(sendBuffer, strlen(sendBuffer));
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}

