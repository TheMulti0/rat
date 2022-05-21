#pragma once

#include <memory>

#include "IConnection.h"
#include "IMessageListener.h"
#include "IMessageSender.h"

class ClientPipe : public IMessageSender, public IMessageListener
{
public:
	ClientPipe(
		std::unique_ptr<IConnection> connection,
		std::unique_ptr<IMessageSender> sender,
		std::unique_ptr<IMessageListener> listener
	);

	ClientPipe(ClientPipe const& t) = delete;

	ClientPipe(ClientPipe&&) noexcept = default;

	ClientPipe& operator=(ClientPipe const&) = delete;

	ClientPipe& operator=(ClientPipe&&) noexcept = default;

	int Send(MessageType type, std::span<char> content) override;

	void Join() override;

private:
	std::unique_ptr<IConnection> _connection;
	std::unique_ptr<IMessageSender> _sender;
	std::unique_ptr<IMessageListener> _listener;
};
