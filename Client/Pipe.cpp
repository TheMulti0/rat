#include "Pipe.h"

#include "ErrorExtensions.h"

Pipe::Pipe(
	SECURITY_ATTRIBUTES attributes,
	bool inheritReadHandle,
	bool inheritWriteHandle)
{
	if (!CreatePipe(&_read, &_write, &attributes, 0))
	{
		ThrowWinApiException("Failed to create pipe");
	}

	if (!SetHandleInformation(_read.get(), HANDLE_FLAG_INHERIT, inheritReadHandle))
	{
		ThrowWinApiException("Failed to set read HANDLE_FLAG_INHERIT to %d", inheritReadHandle);
	}

	if (!SetHandleInformation(_write.get(), HANDLE_FLAG_INHERIT, inheritWriteHandle))
	{
		ThrowWinApiException("Failed to set write HANDLE_FLAG_INHERIT to %d", inheritWriteHandle);
	}
}

HANDLE Pipe::Read() const
{
	auto pointer = _read.get();
	return pointer;
}

HANDLE Pipe::Write() const
{
	auto pointer = _write.get();
	return pointer;
}
