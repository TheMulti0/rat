#pragma once
#include "IConnection.h"

extern "C"
{
	__declspec(dllexport)
	const char* GetAddress(IConnection* connection);
}
