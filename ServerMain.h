#pragma once

#include "Trace.h"
#include "Server.h"
#include "Config.h"

void ServerMain() {
	WinSock winSock;

	Server server = Server(DEFAULT_PORT);

	Trace("server bound\n");

	auto connection = server.WaitForConnection();

	Trace("server got connection\n");

	char receiveBuffer[DEFAULT_BUFLEN];
	connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

	const char* sendBuffer = "Received";
	int size = connection->Send(sendBuffer, strlen(sendBuffer));

	Trace("server sent %d\n", size);

	connection->Shutdown();
}

