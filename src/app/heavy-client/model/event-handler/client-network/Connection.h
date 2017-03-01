#ifndef CLIENT_NETWORK_CONNECTION_H
#define CLIENT_NETWORK_CONNECTION_H

#include <string>
#include <thread>
#include <mutex>
#include <array>
#include <functional>

#include <windows.h>

namespace client_network
{

class Connection
{
public:
	Connection();
	~Connection();

	bool openConnection(const std::string& hostName, const std::string& port);
	void closeConnection();

	void sendMessage(const std::string& message);
	
	template<class F, class T>
	void setOnMessageReceivedHandler(F&& handler, T&& instance);

	template<class F>
	void setOnMessageReceivedHandler(F&& handler);

	template<class F, class T>
	void setOnConnectionLostHandler(F&& handler, T&& object);

	template<class F>
	void setOnConnectionLostHandler(F&& handler);

private:	

	std::function<void(std::string)> onMessageReceived_;
	std::function<void(void)> onConnectionLost_;

	timeval timeout_{ 0, 20000 };
	SOCKET socket_ = INVALID_SOCKET;
	std::thread listener_;
	std::mutex mConnection;
	bool isConnected_ = false;

	static const int DEFAULT_BUFF_LEN = 4096;
	std::array<char, DEFAULT_BUFF_LEN> rcvBuffer_;

	void listen();
	void readData();

	void receiveMessage(const std::string& message);
	void lostConnection();

};

template<class F, class T>
void Connection::setOnMessageReceivedHandler(F&& handler, T&& instance)
{
	onMessageReceived_ = std::bind(handler, instance, std::placeholders::_1);
}

template<class F>
void Connection::setOnMessageReceivedHandler(F&& handler)
{
	onMessageReceived_ = std::bind(handler, std::placeholders::_1);
}

template<class F, class T>
void Connection::setOnConnectionLostHandler(F&& handler, T&& instance)
{
	onConnectionLost_ = std::bind(handler, instance);
}

template<class F>
void Connection::setOnConnectionLostHandler(F&& handler)
{
	onConnectionLost_ = std::bind(handler);
}

}

#endif // CLIENT_NETWORK_CONNECTION_H