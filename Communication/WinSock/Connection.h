#pragma once

#include <string>
#include <WinSock2.h>

#include "IConnection.h"

std::string ToString(const sockaddr_in& address);

class Connection final : public IConnection {
public:
	Connection(const SOCKET& s, const sockaddr_in& address);
	Connection(const SOCKET& s, std::string address);
	~Connection() override;

	std::string GetAddress() override;

	int Send(const char* buffer, int length) override;

	int Receive(char* buffer, int length) override;

	void Shutdown() override;

private:
	SOCKET _socket;
	std::string _address;
};