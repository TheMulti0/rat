#pragma once

#include <memory>

#include "IConnection.h"

class IConnectionFactory
{
public:
	virtual ~IConnectionFactory() = default;

	virtual std::unique_ptr<IConnection> Connect() = 0;
};