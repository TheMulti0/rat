#pragma once

#include "Server.h"
#include "Config.h"

void ServerMain() {
	WinSock winSock;

	Server server = Server(DEFAULT_PORT);
	server.Bind();

	printf("server bound");

	auto connection = server.WaitForConnection();

	printf("server got connection");

	char receiveBuffer[DEFAULT_BUFLEN];
	connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

	const char* sendBuffer = "Received";
	int size = connection->Send(sendBuffer, strlen(sendBuffer));

	printf("server sent %d", size);

	connection->Shutdown();

	server.Unbind();
}

