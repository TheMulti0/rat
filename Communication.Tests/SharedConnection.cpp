#include "SharedConnection.h"

int SharedConnection::Send(const char* buffer, const int length)
{
	_data.insert(_data.end(), buffer, buffer + length);

	return length;
}

int SharedConnection::Receive(char* buffer, const int length)
{
	if (_data.empty())
	{
		return -1;
	}

	std::copy_n(_data.begin(), length, buffer);
	_data.erase(_data.begin(), _data.begin() + length);

	return length;
}

void SharedConnection::Shutdown()
{
}
