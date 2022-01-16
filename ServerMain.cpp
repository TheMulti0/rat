#include "Server.h"
#include "Config.h"

int main() {
	WinSock winSock;

	Server server = Server(DEFAULT_PORT);
	server.Bind();

	auto connection = server.WaitForConnection();

	char receiveBuffer[DEFAULT_BUFLEN];
	connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

	const char* sendBuffer = "Received";
	connection->Send(sendBuffer, strlen(sendBuffer));

	connection->Shutdown();

	server.Unbind();

	return 0;
}

