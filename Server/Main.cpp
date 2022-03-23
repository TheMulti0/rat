#include "IInitializer.h"
#include "ServerMain.h"

int main() {
	std::unique_ptr<IInitializer> initializer = InitializeWinSock();

    ServerMain();

    return 0;
}