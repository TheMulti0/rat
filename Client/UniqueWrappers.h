#pragma once

#include <functional>
#include <memory>
#include <Windows.h>

template<typename T>
using DeletedUniquePtr = std::unique_ptr<T, std::function<void(T)>>;

using UniqueHandle = DeletedUniquePtr<HANDLE>;
//using UniqueHook = DeletedUniquePtr<HHOOK>;

inline UniqueHandle MakeUniqueHandle()
{
	return { new HANDLE(), CloseHandle};
}

inline UniqueHandle MakeUniqueHandle(HANDLE& handle)
{
	return { &handle, CloseHandle };
}

//inline UniqueHook MakeUniqueHook(HHOOK& hook)
//{
//	return { &hook, UnhookWindowsHookEx };
//}