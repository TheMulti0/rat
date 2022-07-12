#pragma once
#include "ICommunicationFactory.h"

extern "C"
{
	__declspec(dllexport)
	ICommunicationFactory* CreateCommunicationFactory();

	__declspec(dllexport)
	IConnectionListener* CreateWinSockConnectionListener(ICommunicationFactory* factory, int port);
}
