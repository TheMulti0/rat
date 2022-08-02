#include <WS2tcpip.h>

#include "Connection.h"
#include "ErrorExtensions.h"

std::string ToString(const sockaddr_in& address)
{
	size_t bufferSize = INET_ADDRSTRLEN;
	const auto ipStr = std::make_unique<char[]>(bufferSize);

	inet_ntop(address.sin_family, &address.sin_addr, ipStr.get(), bufferSize);

	return { ipStr.get(), bufferSize };
}

Connection::Connection(const SOCKET& s, const sockaddr_in& address):
	Connection(s, ToString(address))
{
}

Connection::Connection(const SOCKET& s, std::string address) :
	_socket(s),
	_address(std::move(address))
{
}

Connection::~Connection()
{
	closesocket(_socket);
}

std::string Connection::GetAddress()
{
	return _address;
}

int Connection::Send(const char* buffer, const int length)
{
	const int bytesSent = send(
		_socket,
		buffer,
		length,
		0);

	if (bytesSent == SOCKET_ERROR)
	{
		ThrowWinApiException("Socket send failed");
	}

	return bytesSent;
}

int Connection::Receive(char* buffer, const int length)
{
	const int result = recv(
		_socket, 
		buffer, 
		length, 
		0);

	if (result == SOCKET_ERROR)
	{
		ThrowWinApiException("Socket recv failed");
	}

	return result;
}

void Connection::Shutdown()
{
	const int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		ThrowWinApiException("Socket shutdown failed");
	}
}
