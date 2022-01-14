#include <winsock2.h>
#include <ws2tcpip.h>
#include <exception>

#define DEFAULT_PORT "27015"
#define DEFAULT_IP "127.0.0.1"

class Client {
public:
	Client();
	~Client();

    void Connect();
	int Send(const char* buffer);
	int Receive(char* buffer, int bufferLength);
	void Disconnect();

private:
	addrinfo* _addressInfo;
	SOCKET _socket;

	SOCKET CreateSocket(addrinfo* addressInfo);
    addrinfo* CreateAddressInfo();
    static addrinfo CreateHints();
	void CloseSocket();
};