#pragma once

#include <WinSock2.h>

#include "IConnection.h"

class WinSockConnection : public IConnection {
public:
	explicit WinSockConnection(const SOCKET& s);
	~WinSockConnection() override;

	int Send(const char* buffer, int length) override;

	int Receive(char* buffer, int length) override;

	void Shutdown() override;

private:
	SOCKET _socket;

	void CloseSocket() const;
};