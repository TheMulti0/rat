#include "ServerMain.h"
#include "ClientMain.h"
#include "Trace.h"

#include <thread>
#include <iostream>

int main()
{
	Trace("Hello world %d %s\n", 1, "goodbye");
	std::thread client(ClientMain);
	std::thread server(ServerMain);

	server.join();
	client.join();

	return 0;
}