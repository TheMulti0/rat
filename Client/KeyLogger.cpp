//#include "KeyLogger.h"
//
//KeyLogger::KeyLogger()
//{
//	static std::mutex mutex;
//	std::lock_guard guard(mutex);
//
//	if (_instances.empty())
//	{
//		_hook = std::make_unique<HHOOK>(SetWindowsHookEx(
//			WH_KEYBOARD_LL,
//			&KeyLogger::HookCallback,
//			nullptr,
//			0));
//	}
//
//	_instances.push_back(this);
//}
//
//KeyLogger::~KeyLogger()
//{
//	_instances.emplace_back(this);
//
//	if (_instances.empty())
//	{
//		UnhookWindowsHookEx(*_hook);
//	}
//}
//
//LRESULT KeyLogger::HookCallback(const int nCode, const WPARAM wParam, LPARAM lParam)
//{
//	for (const auto& instance : _instances)
//	{
//		instance->OnKeyboardEvent(nCode, wParam, lParam);
//	}
//
//	return CallNextHookEx(*_hook, nCode, wParam, lParam);
//}
//
//void KeyLogger::OnKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
//{
//}
