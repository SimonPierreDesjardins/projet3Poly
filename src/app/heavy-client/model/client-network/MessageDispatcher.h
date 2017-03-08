#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISAPTCHER_H

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace event_handler
{
	class EventHandler;
}

namespace client_network
{

class MessageDispatcher
{
public:
	MessageDispatcher(event_handler::EventHandler* eventHandler_);
	~MessageDispatcher();

	void startDispatching();
	void stopDispatching();
	void handleReceivedMessage(char const* message, int32_t size);

private:
	bool isDispatching_ = false;
	event_handler::EventHandler* eventHandler_{ nullptr };

	std::string message_;

	std::queue<std::string> messageQueue_;

	std::thread th_;
	std::mutex queueLock_;
	std::mutex lookupLock_;
	std::condition_variable lookupcv_;


	void lookupMessage();
	void dispatch(const std::string& message);
	MessageDispatcher() = delete;
};

}

#endif // MESSAGE_DISPATCHER_