﻿#pragma once

#include <functional>

#include "IConnectionFactory.h"
#include "IConnectionListener.h"
#include "IMessageListener.h"
#include "IMessageSender.h"

class IRat
{
public:
	virtual ~IRat() = default;

	virtual std::unique_ptr<IConnectionFactory> CreateWinSockConnectionFactory(
		const char* ip, int port) = 0;

	virtual std::unique_ptr<IMessageSender> CreateMessageSender(
		IConnection* connection) = 0;

	virtual std::unique_ptr<IConnectionListener> CreateWinSockConnectionListener(
		int port) = 0;

	virtual std::unique_ptr<IMessageListener> CreateMessageListener(
		IConnection* connection,
		std::function<void(MessageType, std::span<char>)> onMessage) = 0;
};

__declspec(dllexport)
std::unique_ptr<IRat> CreateRat();