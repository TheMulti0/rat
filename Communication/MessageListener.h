#pragma once

#include <functional>
#include <thread>

#include "IConnection.h"
#include "IMessageListener.h"
#include "Message.h"
#include "IThreadGuard.h"

class MessageListener final : public IMessageListener
{
public:
	explicit MessageListener(
		IConnection* connection,
		OnMessage onMessage,
		OnDisconnection onDisconnection);

	~MessageListener() override;

	void Join() override;

private:
	void Listen() const;
	std::unique_ptr<Message> ReceiveMessage() const;
	size_t ReceiveMessageLength() const;
	int ReceiveAll(char* buffer, int length) const;

	IConnection* _connection;
	OnMessage _onMessage;
	OnDisconnection _onDisconnection;
	std::atomic_bool _isTerminationRequested;
	std::unique_ptr<IThreadGuard> _thread;
};
