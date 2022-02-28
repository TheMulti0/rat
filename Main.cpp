#include "server/ServerMain.h"
#include "client/ClientMain.h"

#include <thread>

int main()
{
	WinSock winSock;

	std::thread client(ClientMain);
	std::thread server(ServerMain);

	server.join();
	client.join();

	return 0;
}