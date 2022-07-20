#pragma once

#include "IClientPipe.h"
#include "IConnection.h"
#include "IMessageSender.h"

extern "C"
{
	__declspec(dllexport)
	IConnection* GetConnection(IClientPipe* pipe);

	__declspec(dllexport)
	IMessageSender* GetSender(IClientPipe* pipe);
}
