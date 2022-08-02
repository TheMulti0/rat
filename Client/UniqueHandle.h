#pragma once

#include <Windows.h>

class UniqueHandle
{
public:
	UniqueHandle();
	UniqueHandle(const HANDLE& handle);

	UniqueHandle(const UniqueHandle& t) = delete;
	UniqueHandle(UniqueHandle&&) noexcept = default;
	UniqueHandle& operator=(const UniqueHandle &) = delete;
	UniqueHandle& operator=(UniqueHandle&&) noexcept;

	~UniqueHandle();

	HANDLE* Get();

	HANDLE operator*() const;

private:
	HANDLE _handle{};
};
