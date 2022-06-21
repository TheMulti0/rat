#include <WS2tcpip.h>

#include "Connection.h"
#include "Format.h"

std::string InetNtop(const sockaddr_in& address)
{
	char ipStr[INET_ADDRSTRLEN];

	inet_ntop(address.sin_family, &address.sin_addr, ipStr, sizeof ipStr);

	return ipStr;
}

Connection::Connection(const SOCKET& s, const sockaddr_in& address):
	Connection(s, InetNtop(address))
{
}

Connection::Connection(const SOCKET& s, std::string address) :
	_socket(s),
	_address(std::move(address))
{
}

Connection::~Connection()
{
	CloseSocket();
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
		const int error = WSAGetLastError();

		return HandleError(error);

		//throw std::runtime_error(Format("send failed with error: %d", error));
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
		const int error = WSAGetLastError();

		return HandleError(error);

		//throw std::runtime_error(Format("recv failed with error: %d", error));
	}

	return result;
}

void Connection::Shutdown()
{
	const int returnCode = shutdown(_socket, SD_BOTH);

	if (returnCode == SOCKET_ERROR)
	{
		const int error = WSAGetLastError();

		HandleError(error);

		//throw std::runtime_error(Format("shutdown failed with error: %d\n", error));
	}
}

int Connection::HandleError(const int error) const
{
	CloseSocket();

	if (error == WSAECONNRESET || error == WSAESHUTDOWN)
	{
		return error;
	}

	return 0;
}

void Connection::CloseSocket() const
{
	closesocket(_socket);
}
