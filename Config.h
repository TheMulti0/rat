#include <Windows.h>
#include <WinSock2.h>
#include <iostream>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "159823"

struct WinSock {
	WinSock() {
		WSADATA wsaData;
		int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (returnCode != 0) {
			printf("WSAStartup failed with error: %d\n", returnCode);
			throw std::exception();
		}
	}

	~WinSock() {
		WSACleanup();
	}
};