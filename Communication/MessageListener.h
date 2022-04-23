#pragma once

#include <functional>
#include <thread>

#include "IConnection.h"
#include "IMessageListener.h"
#include "Message.h"

class MessageListener final : public IMessageListener
{
public:
	explicit MessageListener(
		IConnection* connection,
		std::function<void(MessageType, std::span<char>)> onMessage);

	~MessageListener() override;

	void Join() override;

private:
	void Listen() const;
	int ReceiveMessageLength() const;
	int ReceiveAll(char* buffer, int length) const;
	std::unique_ptr<Message> ReceiveMessage() const;

	IConnection* _connection;
	std::function<void(MessageType, std::span<char>)> _onMessage;
	std::atomic_bool _isTerminationRequested;
	std::thread _thread;
};
