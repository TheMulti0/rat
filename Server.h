#undef UNICODE

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include "Connection.h"
#include "Config.h"

class Server {
public:
	Server(const char* port);

	void Bind();

	Connection* WaitForConnection();

	void Unbind();

private:
	const char* _port;
	addrinfo* _addressInfo;
	SOCKET _listenSocket;

	addrinfo* CreateAddressInfo();

	addrinfo* ResolveAddressInfo(addrinfo& hints);

	SOCKET CreateListenSocket();

	void ListenForConnections();

	Connection* AcceptClientConnection();
};

Server::Server(const char* port) {
	_port = port;
	_addressInfo = CreateAddressInfo();
	_listenSocket = CreateListenSocket();
}

void Server::Bind() {
	int returnCode = bind(_listenSocket, _addressInfo->ai_addr, (int) _addressInfo->ai_addrlen);

	if (returnCode == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(_addressInfo);
		Unbind();
		throw std::exception();
	}

	freeaddrinfo(_addressInfo);
}

Connection* Server::WaitForConnection() {
	ListenForConnections();

	return AcceptClientConnection();
}

addrinfo* Server::CreateAddressInfo() {
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	return ResolveAddressInfo(hints);
}

void Server::Unbind() { closesocket(_listenSocket); }

Connection* Server::AcceptClientConnection() {
	auto clientSocket = INVALID_SOCKET;

	clientSocket = accept(_listenSocket, nullptr, nullptr);

	if (clientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(_listenSocket);
		throw std::exception();
	}

	return new Connection(clientSocket);
}

void Server::ListenForConnections() {
	int returnCode = listen(_listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(_listenSocket);
		throw std::exception();
	}
}

SOCKET Server::CreateListenSocket() {
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);

	if (listenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(_addressInfo);
		throw std::exception();
	}

	return listenSocket;
}

addrinfo* Server::ResolveAddressInfo(addrinfo& hints) {
	addrinfo* result = nullptr;

	int returnCode = getaddrinfo(nullptr, _port, &hints, &result);

	if (returnCode != 0) {
		printf("getaddrinfo failed with error: %d\n", returnCode);
		throw std::exception();
	}

	return result;
}