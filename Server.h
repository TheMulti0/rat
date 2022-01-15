#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "159823"

void InitializeWinSock();

void CreateAddressInfoHints(addrinfo& hints);

addrinfo* ResolveAddressInfo(addrinfo& hints);

SOCKET CreateListenSocket(addrinfo* addressInfo);

void BindListenSocket(addrinfo* addressInfo, SOCKET listenSocket);

void ListenToConnections(SOCKET listenSocket);

SOCKET AcceptClientConnection(SOCKET listenSocket);

void CloseListenSocket(SOCKET listenSocket);

void ShutdownClientSocket(SOCKET clientSocket);

void Cleanup(SOCKET clientSocket);

int SendBufferBack(SOCKET clientSocket, const char* sendBuffer, int sendBufferLen);

void Receive(SOCKET clientSocket, char* recvBuffer, int recvBufferLen);

void Start() {
	InitializeWinSock();

	addrinfo hints;
	CreateAddressInfoHints(hints);

	addrinfo* addressInfo = ResolveAddressInfo(hints);

	SOCKET listenSocket = CreateListenSocket(addressInfo);

	// Setup the TCP listening socket
	BindListenSocket(addressInfo, listenSocket);

	ListenToConnections(listenSocket);

	SOCKET clientSocket = AcceptClientConnection(listenSocket);

	// Receive until the peer shuts down the connection
	char recvBuffer[DEFAULT_BUFLEN];
	int recvBufferLen = DEFAULT_BUFLEN;
	Receive(clientSocket, recvBuffer, recvBufferLen);

	ShutdownClientSocket(clientSocket);

	CloseListenSocket(listenSocket);
	Cleanup(clientSocket);
}

void Receive(SOCKET clientSocket, char* recvBuffer, int recvBufferLen) {
	int result;

	do {
		result = recv(clientSocket, recvBuffer, recvBufferLen, 0);

		if (result > 0) {
			printf("Bytes received: %d\n", result);

			// Echo the buffer back to the sender
			int sent = SendBufferBack(clientSocket, recvBuffer, result);
			printf("Bytes sent: %d\n", sent);
		}
		else if (result == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			throw std::exception();
		}

	} while (result > 0);
}

int SendBufferBack(SOCKET clientSocket, const char* sendBuffer, int sendBufferLen) {
	int result = send(clientSocket, sendBuffer, sendBufferLen, 0);

	if (result == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		throw std::exception();
	}

	return result;
}

void Cleanup(SOCKET clientSocket) {
	closesocket(clientSocket);
	WSACleanup();
}

void ShutdownClientSocket(SOCKET clientSocket) {
	int returnCode = shutdown(clientSocket, SD_SEND);

	if (returnCode == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		throw std::exception();
	}
}

void CloseListenSocket(SOCKET listenSocket) { closesocket(listenSocket); }

SOCKET AcceptClientConnection(SOCKET listenSocket) {
	auto clientSocket = INVALID_SOCKET;

	clientSocket = accept(listenSocket, nullptr, nullptr);

	if (clientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		throw std::exception();
	}

	return clientSocket;
}

void ListenToConnections(SOCKET listenSocket) {
	int returnCode = listen(listenSocket, SOMAXCONN);

	if (returnCode == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		throw std::exception();
	}
}

void BindListenSocket(addrinfo* addressInfo, SOCKET listenSocket) {
	int returnCode = bind(listenSocket, addressInfo->ai_addr, (int) addressInfo->ai_addrlen);

	if (returnCode == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(addressInfo);
		closesocket(listenSocket);
		WSACleanup();
		throw std::exception();
	}

	freeaddrinfo(addressInfo);
}

SOCKET CreateListenSocket(addrinfo* addressInfo) {
	auto listenSocket = INVALID_SOCKET;

	listenSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);

	if (listenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(addressInfo);
		WSACleanup();
		throw std::exception();
	}

	return listenSocket;
}

addrinfo* ResolveAddressInfo(addrinfo& hints) {
	addrinfo* result = nullptr;

	int returnCode = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);

	if (returnCode != 0) {
		printf("getaddrinfo failed with error: %d\n", returnCode);
		WSACleanup();
		throw std::exception();
	}

	return result;
}

void CreateAddressInfoHints(addrinfo& hints) {
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void InitializeWinSock() {
	WSADATA wsaData;
	int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	if (returnCode != 0) {
		printf("WSAStartup failed with error: %d\n", returnCode);
		throw std::exception();
	}
}
