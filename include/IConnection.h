#pragma once

class IConnection {
public:
	virtual ~IConnection() = default;

	virtual int Send(const char* buffer, int length) = 0;

	virtual int Receive(char* buffer, int length) = 0;

	virtual void Shutdown() = 0;
};