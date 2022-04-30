#pragma once
#include <vector>

#include "ICommunicationFactory.h"
#include "IConnectionListener.h"
#include "IMessageSender.h"
#include "IMessageListener.h"
#include "ThreadGuard.h"
#include "Trace.h"

class ClientPipe : public IMessageSender, public IMessageListener
{
public:
	ClientPipe(
		std::unique_ptr<IConnection> connection,
		std::unique_ptr<IMessageSender> sender,
		std::unique_ptr<IMessageListener> listener
	) :
		_connection(std::move(connection)),
		_sender(std::move(sender)),
		_listener(std::move(listener))
	{
	}

	ClientPipe(ClientPipe const& t) = delete;

	ClientPipe(ClientPipe&&) noexcept = default;

	ClientPipe& operator=(ClientPipe const&) = delete;

	ClientPipe& operator=(ClientPipe&&) noexcept = default;

	int Send(MessageType type, std::span<char> content) override
	{
		return _sender->Send(type, content);
	}

	void Join() override
	{
		_listener->Join();
	}

private:
	std::unique_ptr<IConnection> _connection;
	std::unique_ptr<IMessageSender> _sender;
	std::unique_ptr<IMessageListener> _listener;
};

class RatManager
{
public:
	explicit RatManager(
		ICommunicationFactory* factory,
		std::unique_ptr<IConnectionListener> server
	) :
		_factory(factory),
		_server(std::move(server)),
		_listenThread(std::make_unique<ThreadGuard>(
			std::thread(&RatManager::Listen, this))),
		_clientCount(0),
		_isTerminationRequested(false)
	{
	}

	~RatManager()
	{
		_isTerminationRequested = true;
	}

	[[nodiscard]] int GetClientCount() const
	{
		return _clientCount;
	}

	void Join()
	{
		std::ranges::for_each(
			_clients, 
			[](std::shared_ptr<ClientPipe> client) { client->Join(); });
	}

private:
	void Listen()
	{
		while (!_isTerminationRequested)
		{
			auto client = _server->WaitForConnection();

			auto messageSender = _factory->CreateMessageSender(client.get());

			const auto index = std::make_shared<int>(_clientCount);

			auto messageListener = _factory->CreateMessageListener(
				client.get(),
				[=](auto type, auto content) { OnMessage(*index, type, content); });

			_clients.emplace_back(
				std::make_shared<ClientPipe>(
					std::move(client),
					std::move(messageSender),
					std::move(messageListener)));
			_clientCount++;
		}
	}

	static void OnMessage(
		const int client, 
		const MessageType type, 
		const std::span<char> content)
	{
		Trace(
			"Client %d | %d | %s\n",
			client,
			type,
			std::string(content.data(), content.size()).c_str()
		);
	}

	ICommunicationFactory* _factory;
	std::unique_ptr<IConnectionListener> _server;
	std::vector<std::shared_ptr<ClientPipe>> _clients;
	std::unique_ptr<ThreadGuard> _listenThread;
	int _clientCount;
	bool _isTerminationRequested;
};

