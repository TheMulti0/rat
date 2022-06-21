#pragma once

#include <vector>

#include "IConnection.h"

class SharedConnection final : public IConnection
{
public:
	std::string GetAddress() override;

	int Send(const char* buffer, int length) override;

	int Receive(char* buffer, int length) override;

	void Shutdown() override;

private:
	std::vector<char> _data;
};

