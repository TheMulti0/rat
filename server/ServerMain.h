#pragma once

#include "../shared/Trace.h"
#include "Server.h"
#include "../shared/WinSock.h"

void ServerMain() {
	Server server = Server(DEFAULT_PORT);

	auto connection = server.WaitForConnection();

	char receiveBuffer[DEFAULT_BUFLEN];
	int bytesReceived;

	do {
		bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

		std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

		Trace("SERVER: Received %s\n", message.c_str());

		connection->Send(message.c_str(), message.length());

        Trace("SERVER: Sent %s\n", message.c_str());
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}

