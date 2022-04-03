#include <memory>

#include "IConnectionListener.h"
#include "Trace.h"
#include "IRat.h"
#include "MessageType.h"

int main() {
	const auto rat = CreateRat();
	const auto server = rat->CreateWinSockConnectionListener(4444);
	const auto connection = server->WaitForConnection();

	auto listener = rat->CreateMessageListener(
		connection.get(),
		[](MessageType type, const std::string message)
		{
			Trace("SERVER: Received %s\n", message.c_str());
		});
	//connection->Shutdown();

	return 0;
}
