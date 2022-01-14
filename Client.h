#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void InitializeWinSock();

addrinfo CreateAddressInfoHints();

addrinfo* ResolveAddressInfo(addrinfo& hints, const char* ip, const char* port);

SOCKET ConnectToServer(addrinfo* result);

int Send(SOCKET socket, const char* sendBuffer);

void ShutdownSocket(SOCKET socket);

void Receive(SOCKET socket, char* recvBuffer, int recvBufferLen);

void Cleanup(SOCKET socket);

void Start(const char* ip) {
	// Initialize Winsock
	InitializeWinSock();

	addrinfo hints = CreateAddressInfoHints();

	const char* port = DEFAULT_PORT;

	// Resolve the server address and port
	addrinfo* result = ResolveAddressInfo(hints, ip, port);

	SOCKET socket = ConnectToServer(result);

	if (socket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		throw std::exception();
	}

	// Send an initial buffer
	const char* sendBuffer = "this is a test";
	int sent = Send(socket, sendBuffer);
	printf("Bytes Sent: %ld\n", sent);

	// shutdown the connection since no more data will be sent
	ShutdownSocket(socket);

	char recvBuffer[DEFAULT_BUFLEN];
	int recvBufferLen = DEFAULT_BUFLEN;

	// Receive until the peer closes the connection
	Receive(socket, recvBuffer, recvBufferLen);

	// cleanup
	Cleanup(socket);
}

void Cleanup(SOCKET socket) {
	closesocket(socket);
	WSACleanup();
}

void Receive(SOCKET socket, char* recvBuffer, int recvBufferLen) {
	int returnCode;

	do {
		returnCode = recv(socket, recvBuffer, recvBufferLen, 0);

		if (returnCode > 0)
			printf("Bytes received: %d\n", returnCode);
		else if (returnCode == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (returnCode > 0);
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

SOCKET ConnectToServer(addrinfo* result) {
	addrinfo* ptr;
	auto socket = INVALID_SOCKET;

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (socket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			throw std::exception();
		}

		// Connect to server.
		int returnCode = connect(socket, ptr->ai_addr, (int) ptr->ai_addrlen);

		if (returnCode == SOCKET_ERROR) {
			closesocket(socket);
			socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	return socket;
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

addrinfo CreateAddressInfoHints() {
	addrinfo hints;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	return hints;
}

void InitializeWinSock() {
	WSADATA wsaData;
	int returnCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (returnCode != 0) {
		printf("WSAStartup failed with error: %d\n", returnCode);
		throw std::exception();
	}
}
