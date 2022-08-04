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

void GetClients(IRatManager* manager, ClientInfo* infos)
{
	*infos = *manager->GetClients();
}

int Send(
	const IRatManager* manager,
	const int client,
	const MessageType type,
	char* content,
	const int contentLength)
{
	auto contentSpan = SharedSpan(contentLength);

	std::copy_n(content, contentLength, contentSpan.Data());

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