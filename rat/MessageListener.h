#pragma once

#include <functional>
#include <thread>

#include "IConnection.h"
#include "IMessageListener.h"
#include "Message.h"

class MessageListener : public IMessageListener
{
public:
	explicit MessageListener(
		IConnection* connection,
		std::function<void(MessageType, std::string)> onMessage);
	~MessageListener() override;

private:
	void Listen() const;
	int ReceiveMessageLength() const;
	int ReceiveAll(char* buffer, int length) const;
	std::unique_ptr<Message> ReceiveMessage() const;

	std::unique_ptr<IConnection> _connection;
	std::function<void(MessageType, std::string)> _onMessage;
	std::thread _thread;
};
