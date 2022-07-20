#pragma once

#include "IMessageSender.h"

extern "C"
{
	__declspec(dllexport)
	int Send(
		const IMessageSender* sender,
		MessageType type,
		char* content,
		int contentLength);
}
