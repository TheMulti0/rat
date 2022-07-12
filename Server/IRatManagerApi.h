#pragma once

#include "IRatManager.h"

extern "C"
{
	__declspec(dllexport)
	IRatManager* CreateRatManager(int port);

	__declspec(dllexport)
	int GetClientCount(const IRatManager* manager);

	__declspec(dllexport)
	int Send(
		const IRatManager* manager,
		int client, 
		MessageType type, 
		char* content, 
		int contentLength);

	__declspec(dllexport)
	void Join(IRatManager* manager);

	__declspec(dllexport)
	void DisposeRatManager(const IRatManager* manager);
}
