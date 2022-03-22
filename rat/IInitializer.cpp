#include "IInitializer.h"
#include "WinSockInitializer.h"

std::unique_ptr<IInitializer> InitializeWinSock()
{
	return std::make_unique<WinSockInitializer>();
}