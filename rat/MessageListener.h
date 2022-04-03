#pragma once

#include <thread>

#include "IMessageListener.h"

class MessageListener : public IMessageListener
{
public:
	explicit MessageListener(
		IConnection* connection,
		void (*onMessage)(MessageType, std::string));
	~MessageListener() override;

private:
	void Listen() const;
	int ReceiveMessageLength() const;
	int ReceiveAll(char* buffer, int length) const;
	std::unique_ptr<Message> ReceiveMessage() const;

	std::unique_ptr<IConnection> _connection;
	void (*_onMessage)(MessageType, std::string);
	std::thread _thread;
};