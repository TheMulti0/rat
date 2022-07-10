#pragma once

#include <string>

class ISingleProcessManager
{
public:
	virtual ~ISingleProcessManager() = default;

	virtual void Run(std::wstring name) = 0;

	virtual void WriteToStdIn(std::string text) = 0;
};

