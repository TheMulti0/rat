#pragma once

#include <memory>

#include "IConnection.h"

class IConnectionListener
{
public:
	virtual ~IConnectionListener() = default;

	virtual std::unique_ptr<IConnection> WaitForConnection() = 0;
};