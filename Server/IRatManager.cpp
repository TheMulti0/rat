#include "IRatManager.h"
#include "RatManager.h"

std::unique_ptr<IRatManager> CreateRatManager(
	ICommunicationFactory* factory,
	std::unique_ptr<IConnectionListener> server)
{
	return std::make_unique<RatManager>(factory, std::move(server));
}