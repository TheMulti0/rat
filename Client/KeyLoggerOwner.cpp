#include "KeyLoggerOwner.h"

KeyLoggerOwner::KeyLoggerOwner(OnKeyLog onKeyLog) :
	_onKeyLog(std::move(onKeyLog)),
	_thread(MakeThreadGuard(std::thread(&KeyLoggerOwner::MessageLoop, this))),
	_isCancellationRequested(false)
{
}

KeyLoggerOwner::~KeyLoggerOwner()
{
	_isCancellationRequested = true;
}

void KeyLoggerOwner::MessageLoop()
{
	_keyLogger = std::make_unique<KeyLogger>(_onKeyLog);

	MSG message;

	while (
		!_isCancellationRequested && 
		GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}
