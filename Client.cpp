#include <memory>
#include "Client.h"

Client::Client() {
	_addressInfo = CreateAddressInfo();
	_socket = CreateSocket(_addressInfo);
}

Client::~Client() = default;

void Client::Connect() {
	int returnCode = connect(
            _socket,
            _addressInfo->ai_addr,
            (int) _addressInfo->ai_addrlen);

    if (returnCode == SOCKET_ERROR) {
		CloseSocket();
		throw std::exception();
    }
}

int Client::Send(const char* buffer) {
	int bytesToSend = (int) strlen(buffer);

	int result = send(_socket, buffer, bytesToSend, 0);

	if (result == SOCKET_ERROR) {
		CloseSocket();
		throw std::exception();
	}

	return result;
}

int Client::Receive(char* buffer, int bufferLength) {
	int result = recv(_socket, buffer, bufferLength, 0);

	if (result == SOCKET_ERROR) {
		CloseSocket();
		throw std::exception();
	}

	return result;
}

void Client::Disconnect() {
	int returnCode = shutdown(_socket, SD_SEND);

	if (returnCode == SOCKET_ERROR) {
		CloseSocket();
		throw std::exception();
	}
}

void Client::CloseSocket() {
	closesocket(_socket);
}

addrinfo Client::CreateHints() {
    addrinfo hints{};
    // For this application, the Internet address family is unspecified so that either an IPv6 or IPv4 address can be returned.
    hints.ai_family = AF_UNSPEC;
    // The application requests the socket type to be a stream socket for the TCP protocol.
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    return hints;
}

addrinfo* Client::CreateAddressInfo() {
    addrinfo hints = CreateHints();

    addrinfo* pResult{};

    int returnCode = getaddrinfo(
            DEFAULT_IP,
            DEFAULT_PORT,
            &hints,
            &pResult);

    if (returnCode != 0) {
        throw std::exception();
    }

	return pResult;
}

SOCKET Client::CreateSocket(addrinfo* addressInfo) {
    SOCKET connectSocket = socket(
            addressInfo->ai_family,
            addressInfo->ai_socktype,
            addressInfo->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        freeaddrinfo(addressInfo);
        throw std::exception();
    }

    return connectSocket;
}
