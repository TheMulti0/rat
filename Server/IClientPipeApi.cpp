#include "IClientPipeApi.h"

IConnection* GetConnection(IClientPipe* pipe)
{
	return pipe->GetConnection();
}

IMessageSender* GetSender(IClientPipe* pipe)
{
	return pipe->GetSender();
}
