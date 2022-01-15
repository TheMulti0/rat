#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "159823"

void InitializeWinSock();

void CreateAddressInfoHints(addrinfo& hints);

addrinfo* ResolveAddressInfo(addrinfo& hints, const char* ip, const char* port);

SOCKET ConnectToServer(addrinfo* addressInfo);

int Send(SOCKET socket, const char* sendBuffer);

void ShutdownSocket(SOCKET socket);

void Receive(SOCKET socket, char* recvBuffer, int recvBufferLen);

void Cleanup(SOCKET socket);

void Start(const char* ip) {
	InitializeWinSock();

	addrinfo hints;
	CreateAddressInfoHints(hints);

	const char* port = DEFAULT_PORT;

	addrinfo* addressInfo = ResolveAddressInfo(hints, ip, port);

	SOCKET socket = ConnectToServer(addressInfo);

	while (true) {
		printf("Enter text to send (type 'cancel' to stop)");
		std::string sendBuffer;
		std::cin >> sendBuffer;

		if (sendBuffer == "cancel") {
			break;
		}

		int sent = Send(socket, sendBuffer.c_str());
		printf("Bytes sent: %ld\n", sent);

		char recvBuffer[DEFAULT_BUFLEN];
		int recvBufferLen = DEFAULT_BUFLEN;

		// Receive until the peer closes the connection
		Receive(socket, recvBuffer, recvBufferLen);
	}

	ShutdownSocket(socket);
	Cleanup(socket);
}

void Cleanup(SOCKET socket) {
	closesocket(socket);
	WSACleanup();
}

void Receive(SOCKET socket, char* recvBuffer, int recvBufferLen) {
	int result;

	do {
		result = recv(socket, recvBuffer, recvBufferLen, 0);

		if (result > 0)
		{
			printf("Bytes received: %d\n", result);
			printf("Received: %s", recvBuffer);
		}
		else if (result == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
		}

	} while (result > 0);
}

void ShutdownSocket(SOCKET socket) {
	int returnCode = shutdown(socket, SD_SEND);

	if (returnCode == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		WSACleanup();
		throw std::exception();
	}
}

int Send(SOCKET socket, const char* sendBuffer) {
	int result = send(socket, sendBuffer, (int) strlen(sendBuffer), 0);

	if (result == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		WSACleanup();
		throw std::exception();
	}

	return result;
}

SOCKET ConnectToServer(addrinfo* addressInfo) {
	addrinfo* ptr;
	auto connectSocket = INVALID_SOCKET;

	// Attempt to connect to an address until one succeeds
	for (ptr = addressInfo; ptr != nullptr; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (connectSocket == INVALID_SOCKET) {
			printf("connectSocket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			throw std::exception();
		}

		// Connect to server.
		int returnCode = connect(connectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);

		if (returnCode == SOCKET_ERROR) {
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(addressInfo);

	if (connectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		throw std::exception();
	}

	return connectSocket;
}

addrinfo* ResolveAddressInfo(addrinfo& hints, const char* ip, const char* port) {
	addrinfo* result = nullptr;

	int returnCode = getaddrinfo(ip, port, &hints, &result);

	if (returnCode != 0) {
		printf("getaddrinfo failed with error: %d\n", returnCode);
		WSACleanup();
		throw std::exception();
	}

	return result;
}

void CreateAddressInfoHints(addrinfo& hints) {
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void InitializeWinSock() {
	WSADATA wsaData;
	int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (returnCode != 0) {
		printf("WSAStartup failed with error: %d\n", returnCode);
		throw std::exception();
	}
}
