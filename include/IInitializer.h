#pragma once

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 11111

#include <memory>

class IInitializer {
public:
	virtual ~IInitializer() = default;
};

__declspec(dllexport)
std::unique_ptr<IInitializer> InitializeWinSock();