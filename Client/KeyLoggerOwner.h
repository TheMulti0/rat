#pragma once

#include "IThreadGuard.h"
#include "KeyLogger.h"

class KeyLoggerOwner
{
public:
	explicit KeyLoggerOwner(OnKeyLog onKeyLog);

	~KeyLoggerOwner();

private:
	void MessageLoop();

	OnKeyLog _onKeyLog;
	std::unique_ptr<IThreadGuard> _thread;
	std::unique_ptr<KeyLogger> _keyLogger;
	std::atomic_bool _isCancellationRequested;
};

