#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#include "Config.h"
#include "Connection.h"

class Client {
public:
	Client(const char* ip, const char* port);

	Connection* Connect();

private:
	addrinfo* _addressInfo;

	addrinfo* CreateAddressInfo(const char* ip, const char* port);

	addrinfo* ResolveAddressInfo(addrinfo& hints, const char* ip, const char* port);

	SOCKET ConnectToServer();
};

Client::Client(const char* ip, const char* port) {
	_addressInfo = CreateAddressInfo(ip, port);
}

Connection* Client::Connect() {
	auto connectSocket = ConnectToServer();

	freeaddrinfo(_addressInfo);

	if (connectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		CleanupWinSock();
		throw std::exception();
	}

	return new Connection(connectSocket);
}

addrinfo* Client::CreateAddressInfo(const char* ip, const char* port) {
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	return ResolveAddressInfo(hints, ip, port);
}

addrinfo* Client::ResolveAddressInfo(addrinfo& hints, const char* ip, const char* port) {
	addrinfo* result = nullptr;

	int returnCode = getaddrinfo(ip, port, &hints, &result);

	if (returnCode != 0) {
		printf("getaddrinfo failed with error: %d\n", returnCode);
		CleanupWinSock();
		throw std::exception();
	}

	return result;
}

SOCKET Client::ConnectToServer() {
	auto connectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server
	connectSocket = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);

	if (connectSocket == INVALID_SOCKET) {
		printf("connectSocket failed with error: %ld\n", WSAGetLastError());
		CleanupWinSock();
		throw std::exception();
	}

	// Connect to server
	int returnCode = connect(connectSocket, _addressInfo->ai_addr, (int) _addressInfo->ai_addrlen);

	if (returnCode == SOCKET_ERROR) {
		closesocket(connectSocket);
		return INVALID_SOCKET;
	}

	return connectSocket;
}
