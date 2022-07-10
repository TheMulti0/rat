#pragma once

#include "ICommunicationFactory.h"

class IRat
{
};

__declspec(dllexport)
std::unique_ptr<IRat> CreateRat(
	ICommunicationFactory* factory,
	std::unique_ptr<IConnectionFactory> client);