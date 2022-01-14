#include <iostream>
#include <memory>
#include <WinSock2.h>
#include "Client.h"

void InitializeWinSock() {
    WSADATA wsaData;

    int startup = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (startup != 0) {
        throw std::exception();
    }
}

int main() {
    std::unique_ptr<Client> client = std::make_unique<Client>();
    InitializeWinSock();

    try {
        addrinfo *result = GetAddressInfo();

        SOCKET socket = GetConnectSocket(result);
    }
    catch (std::exception& e) {
        WSACleanup();
        throw e;
    }

    return 0;
}
