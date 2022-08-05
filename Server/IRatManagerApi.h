#pragma once

#include "IRatManager.h"

extern "C"
{
	__declspec(dllexport)
	IRatManager* CreateRatManager(int port);

	__declspec(dllexport)
	int GetClientCount(const IRatManager* manager);

	__declspec(dllexport)
	void GetClients(IRatManager* manager, ClientInfo* infos);

	__declspec(dllexport)
	void Send(
		IRatManager* manager,
		int client, 
		MessageType type, 
		char* content, 
		int contentLength);

	__declspec(dllexport)
	void Join(IRatManager* manager);

	__declspec(dllexport)
	void DisposeRatManager(const IRatManager* manager);
}
