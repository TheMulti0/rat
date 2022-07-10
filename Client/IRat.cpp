#include "IRat.h"

#include "Rat.h"

std::unique_ptr<IRat> CreateRat(
	ICommunicationFactory* factory,
	std::unique_ptr<IConnectionFactory> client)
{
	return std::make_unique<Rat>(factory, std::move(client));
}
