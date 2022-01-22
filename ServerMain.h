#pragma once

#include "Trace.h"
#include "Server.h"
#include "WinSock.h"

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
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}

