#pragma once

#include <memory>
#include <string>

#include "Trace.h"
#include "Server.h"

void ServerMain() {
	const auto server = std::make_unique<Server>(DEFAULT_PORT);

	const auto connection = server->WaitForConnection();

	int bytesReceived;

	do {
		char receiveBuffer[DEFAULT_BUFLEN];
		bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

		std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

		Trace("SERVER: Received %s\n", message.c_str());

		connection->Send(message.c_str(), message.length());

        Trace("SERVER: Sent %s\n", message.c_str());
	}
	while (bytesReceived > 0);

	connection->Shutdown();
}

