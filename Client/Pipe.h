#pragma once

#include <Windows.h>

#include "UniqueHandle.h"

class Pipe
{
public:
	explicit Pipe(
		SECURITY_ATTRIBUTES attributes
	);

	HANDLE Read() const;
	HANDLE Write() const;

private:
	UniqueHandle _read;
	UniqueHandle _write;
};
