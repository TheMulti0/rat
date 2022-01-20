#include "ServerMain.h"
#include "ClientMain.h"

#include <thread>
#include <iostream>

int main()
{
	std::thread server(ServerMain);
	std::thread client(ClientMain);

	server.join();
	client.join();

	return 0;
}