#pragma once

#include "ICommunicationFactory.h"

class IRat
{
};

__declspec(dllexport)
std::unique_ptr<IRat> CreateRat(
	ICommunicationFactory* factory,
	const char* ip,
	int port);