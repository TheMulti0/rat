#include "ClientMain.h"

int main() {
	std::unique_ptr<IInitializer> initializer = InitializeWinSock();

    ClientMain();

    return 0;
}