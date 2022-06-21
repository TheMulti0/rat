#pragma once

#include <string>

class IConnection {
public:
	virtual ~IConnection() = default;

	virtual std::string GetAddress() = 0;

	virtual int Send(const char* buffer, int length) = 0;

	virtual int Receive(char* buffer, int length) = 0;

	virtual void Shutdown() = 0;
};