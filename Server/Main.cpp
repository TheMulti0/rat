#include <memory>

#include "Trace.h"
#include "IInitializer.h"
#include "IMessageListener.h"
#include "Server.h"

int main() {
	std::unique_ptr<IInitializer> initializer = InitializeWinSock();

	const auto server = std::make_unique<Server>(DEFAULT_PORT);
	const auto connection = server->WaitForConnection();

	//int bytesReceived;

	//do {
	//	char receiveBuffer[DEFAULT_BUFLEN];
	//	bytesReceived = connection->Receive(receiveBuffer, DEFAULT_BUFLEN);

	//	std::string message = std::string(receiveBuffer).substr(0, bytesReceived);

	//	Trace("SERVER: Received %s\n", message.c_str());

	//	connection->Send(message.c_str(), message.length());

	//	Trace("SERVER: Sent %s\n", message.c_str());
	//}
	//while (bytesReceived > 0);

	auto listener = CreateMessageListener(connection.get(), [](MessageType type, std::string message)
	{
		Trace("SERVER: Received %s\n", message.c_str());
	});
	//connection->Shutdown();

	return 0;
}