#pragma once

class IMessageListener
{
public:
	virtual ~IMessageListener() = default;

	virtual void Join() = 0;
};
