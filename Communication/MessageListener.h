#pragma once

#include <functional>
#include <thread>

#include "IConnection.h"
#include "IMessageListener.h"
#include "Message.h"
#include "ThreadGuard.h"

class MessageListener final : public IMessageListener
{
public:
	explicit MessageListener(
		IConnection* connection,
		std::function<void(MessageType, std::span<char>)> onMessage,
		std::function<void()> onDisconnection);

	~MessageListener() override;

	void Join() override;

private:
	void Listen() const;
	std::unique_ptr<Message> ReceiveMessage() const;
	int ReceiveMessageLength() const;
	int ReceiveAll(char* buffer, int length) const;

	IConnection* _connection;
	std::function<void(MessageType, std::span<char>)> _onMessage;
	std::function<void()> _onDisconnection;
	std::atomic_bool _isTerminationRequested;
	std::unique_ptr<ThreadGuard> _thread;
};
