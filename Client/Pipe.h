#pragma once

#include <Windows.h>
#include <wil/resource.h>

class Pipe
{
public:
	explicit Pipe(
		SECURITY_ATTRIBUTES attributes,
		bool inheritReadHandle,
		bool inheritWriteHandle
	);

	HANDLE Read() const;
	HANDLE Write() const;

private:
	wil::unique_handle _read;
	wil::unique_handle _write;
};
