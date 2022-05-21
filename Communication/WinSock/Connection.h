#pragma once

#include <WinSock2.h>

#include "IConnection.h"

class Connection final : public IConnection {
public:
	explicit Connection(const SOCKET& s);
	~Connection() override;

	int Send(const char* buffer, int length) override;

	int Receive(char* buffer, int length) override;

	void Shutdown() override;

private:
	SOCKET _socket;

	int HandleError(int error) const;

	void CloseSocket() const;
};