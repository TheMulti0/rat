#pragma once

#include <span>

#include "Windows.h"

#include "IMessageHandler.h"

class CreateProcessHandler : public IMessageHandler
{
public:
	void Handle(std::span<char> content) override;

	static void Create(LPWSTR name);
};
