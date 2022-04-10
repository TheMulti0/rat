#include <memory>

#include "IConnectionListener.h"
#include "Trace.h"
#include "IRat.h"
#include "MessageType.h"

int main() {
	const auto rat = CreateRat();
	const auto server = rat->CreateWinSockConnectionListener(4444);
	const auto connection = server->WaitForConnection();
	static const auto sender = rat->CreateMessageSender(connection.get());

	auto listener = rat->CreateMessageListener(
		connection.get(),
		[](MessageType type, const std::string message)
		{
			Trace("SERVER: Received %s\n", message.c_str());
			if (type == MessageType::Ping)
			{
				using namespace std::chrono;
				auto tp = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
				auto dp = floor<days>(tp);
				year_month_day ymd{ dp };
				auto a = floor<nanoseconds>(tp - dp);

				
				const long long stoi = std::stoll(message);
				const auto ping = a.count() - stoi;

				const std::string buffer = "Ping is " + std::to_string(ping);
				sender->Send(MessageType::Ping, buffer);
				Trace("Sending ping %s", buffer.c_str());
			}
		});
	//connection->Shutdown();

	return 0;
}
