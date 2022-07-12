#include "CommunicationFactoryApi.h"

#include "ICommunicationFactory.h"

ICommunicationFactory* CreateCommunicationFactory()
{
	return CreateFactory().release();
}

IConnectionListener* CreateWinSockConnectionListener(ICommunicationFactory* factory, int port)
{
	return factory->CreateWinSockConnectionListener(port).release();
}
