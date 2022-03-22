#pragma once

#include <WinSock2.h>
#include <memory>

class IConnection {
public:
	virtual ~IConnection() = default;

	virtual int Send(const char* buffer, int length) = 0 ;

	virtual int Receive(char* buffer, int length) = 0;

	virtual void Shutdown() = 0;
};

__declspec(dllexport)
std::unique_ptr<IConnection> CreateWinSockConnection(const SOCKET& s);