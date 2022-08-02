#include "UniqueHandle.h"

UniqueHandle::UniqueHandle()
{
}

UniqueHandle::UniqueHandle(const HANDLE& handle) : _handle(handle)
{
}

UniqueHandle& UniqueHandle::operator=(UniqueHandle&& h) noexcept
{
	const auto m = h._handle;
	h._handle = _handle;
	_handle = m;

	return *this;
}

UniqueHandle::~UniqueHandle()
{
	if (_handle != nullptr)
	{
		CloseHandle(_handle);
	}
}

HANDLE* UniqueHandle::Get()
{
	return &_handle;
}

HANDLE UniqueHandle::operator*() const
{
	return _handle;
}