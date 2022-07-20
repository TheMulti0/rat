#include "IRatManagerApi.h"

#include "IRatManager.h"

IRatManager* CreateRatManager(const int port)
{
	auto factory = CreateFactory();

	return CreateRatManager(
			factory.release(),
			factory->CreateWinSockConnectionListener(port))
		.release();
}

int GetClientCount(const IRatManager* manager)
{
	return manager->GetClientCount();
}

IClientPipe** GetClients(IRatManager* manager)
{
	const auto clients = manager->GetClients();

	const auto clientsRaw = new IClientPipe* [clients.size()];
	int index = 0;

	for (const auto& client : manager->GetClients())
	{
		IClientPipe* clientCopy = nullptr;
		std::memcpy(&clientCopy, client.get(), sizeof client);

		clientsRaw[index] = clientCopy;
		index++;
	}

	return clientsRaw;
}

int Send(
	const IRatManager* manager,
	const int client,
	const MessageType type,
	char* content,
	const int contentLength)
{
	const auto contentSpan = std::span(content, contentLength);

	return manager->Send(client, type, contentSpan);
}

void Join(IRatManager* manager)
{
	manager->Join();
}

void DisposeRatManager(const IRatManager* manager)
{
	if (manager == nullptr)
	{
		return;
	}

	delete manager;
	manager = nullptr;
}