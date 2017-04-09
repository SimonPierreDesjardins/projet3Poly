#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISAPTCHER_H

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Serializer.h"

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
	void handleReceivedMessage(char const* message, uint32_t size);


private:
	bool isDispatching_ = false;
	event_handler::EventHandler* eventHandler_{ nullptr };

	std::queue<std::string> messageQueue_;

	std::thread th_;
	std::mutex queueLock_;
	std::mutex lookupLock_;
	std::condition_variable lookupcv_;

	Serializer serializer_;

	void lookupMessage();

	void pushMessage(const std::string& message);
	void dispatch(const std::string& message);

	// Physic message
	void handlePhysicMessage(const std::string& message);
	void handleSinglePhysicMessage(const std::string& message);
	void handleStackedPhysicsMessage(const std::string& message);

	// Map idition message
	void handleMapEditionMessage(const std::string& message);
	void handleEntityCreationMessage(const std::string& message);
	void handleEntityDeletionMessage(const std::string& message);
	void handleEntitySelectionMessage(const std::string& message);

	// User sustem message
	void handleUserAuthentificationConfirmation(const std::string& message);
	void handleUserCreationConfirmation(const std::string& message);
	void handleUserSystemMessage(const std::string& message);

	// Map systemMessage
	void handleMapSystemMessage(const std::string& message);
	void handleMapCreationMessage(const std::string& message);
	void handleMapJoinMessage(const std::string& message);
	void handleMapQuitMessage(const std::string& message);
	void handleMapListMessage(const std::string& message);
	void handleMapReadyMessage(const std::string& message);
	void handleMapPermissionMessage(const std::string& message);

	MessageDispatcher() = delete;

	unsigned int lengthBytesLeft_ = 4;
	char lengthBytes_[4];
	unsigned int messageBytesLeft_ = 0;
	std::string currentMessage_ = "";
};

}

#endif // MESSAGE_DISPATCHER_