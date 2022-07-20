#include "IConnectionApi.h"

const char* GetAddress(IConnection* connection)
{
	auto address = connection->GetAddress();

	const auto addressPtr = new char[address.length() + 1];

	std::ranges::copy(address, addressPtr);

	return addressPtr;
}
