#include "IRat.h"

#include "Rat.h"

std::unique_ptr<IRat> CreateRat(
	ICommunicationFactory* factory,
	const char* ip,
	const int port)
{
	return std::make_unique<Rat>(factory, ip, port);
}
