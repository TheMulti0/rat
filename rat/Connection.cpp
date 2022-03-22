#include "IConnection.h"
#include "WinSockConnection.h"

std::unique_ptr<IConnection> CreateWinSockConnection(const SOCKET& s)
{
	return std::make_unique<WinSockConnection>(s);
}
