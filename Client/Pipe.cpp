#include "Pipe.h"

Pipe::Pipe(SECURITY_ATTRIBUTES attributes):
	_read(UniqueHandle()),
	_write(UniqueHandle())
{
	CreatePipe(_read.Get(), _write.Get(), &attributes, 0);
	SetHandleInformation(*_read, HANDLE_FLAG_INHERIT, 0);
}

HANDLE Pipe::Read() const
{
	return *_read;
}

HANDLE Pipe::Write() const
{
	return *_write;
}
