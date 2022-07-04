#pragma once

#include <map>
#include <memory>

#include "RatManager.h"

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

	void ListClients() const;

	void ParseInput();

	std::map<std::string, std::function<void()>> _commands;
	std::unique_ptr<ICommunicationFactory> _factory;
	std::unique_ptr<RatManager> _manager;
	std::string _command;
	std::string _args;
};

