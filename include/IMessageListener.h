#pragma once

#include <functional>

#include "MessageType.h"
#include "SharedSpan.h"

using OnMessage = std::function<void(MessageType, SharedSpan)>;
using OnDisconnection = std::function<void()>;

class IMessageListener
{
public:
	virtual ~IMessageListener() = default;

	virtual void Join() = 0;
};
