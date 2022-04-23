#include <memory>

#include "IConnectionListener.h"
#include "Trace.h"
#include "ICommunicationFactory.h"
#include "MessageType.h"

int main() {
	const auto rat = CreateFactory();
	const auto server = rat->CreateWinSockConnectionListener(4444);
	const auto connection = server->WaitForConnection();
	static const auto sender = rat->CreateMessageSender(connection.get());

	auto listener = rat->CreateMessageListener(
		connection.get(),
		[](MessageType type, const std::span<char> content)
		{
			std::string message = std::string(content.begin(), content.end());

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
				auto cStr = buffer.c_str();
				auto content = *reinterpret_cast<std::span<char>*>(&cStr);

				sender->Send(MessageType::Ping, content);
				Trace("Sending ping %s", cStr);
			}
		});
	//connection->Shutdown();

	return 0;
}
