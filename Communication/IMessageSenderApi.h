#pragma once

#include "IMessageSender.h"

extern "C"
{
	__declspec(dllexport)
	void Send(
		const IMessageSender* sender,
		MessageType type,
		char* content,
		int contentLength);
}
