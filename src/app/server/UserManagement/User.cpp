#include "User.h"
#include <iostream>

namespace server
{

server::User::User(UserInformation & userInfo)
	: Info(userInfo)
{
	UserCount++;
	StartMessageReadThread();
	_connection = nullptr;
}

User::~User()
{
	Networking::NetworkObjects::Dispose(_connection);
	UserCount--;
	if (UserCount == 0) {
		StopMessageReadThread();
	}
}

void User::AssignConnection(Networking::Connection * connectionToTreat)
{
	_connection = connectionToTreat;
	HookToConnection(connectionToTreat);
}

void User::HookToConnection(Networking::Connection * connectionToListenTo)
{
	_connection->hookOnReceivedMessage(&User::OnReceivedMessage, this);
	_connection->hookOnConnectionLost(&User::OnConnectionLost, this);
}

void User::OnReceivedMessage(const std::string& message)
{
	_queueMutex.lock();
	_messageQueue.push(std::move(std::make_pair(this, message)));
	_queueMutex.unlock();
}

void User::OnConnectionLost()
{
	notifyDisconnected(this);
}

void User::StartMessageReadThread()
{

	if (_runThread) {
		return;
	}
	_runThread = true;

	_messageReaderThread = new std::thread([](){
		std::pair<User*, std::string> userMessagePair;
		while (_runThread) {
			_queueMutex.lock();
			if (_messageQueue.size() > 0) {
				userMessagePair = std::move(_messageQueue.front());
				_messageQueue.pop();
				// We release the queue ASAP so it can receive new messages
				_queueMutex.unlock();

				// treat the message
				userMessagePair.first->dispatchReceivedMessage(userMessagePair.first, userMessagePair.second);
			}
			else {
				_queueMutex.unlock();
			}
		}
	});
}

void User::StopMessageReadThread()
{
	_runThread = false;
	while (!_messageReaderThread->joinable()) {}
	_messageReaderThread->join();
}

std::queue<std::pair<User*, std::string>> User::_messageQueue;
std::mutex User::_queueMutex;
std::thread* User::_messageReaderThread = nullptr;
bool User::_runThread = false;
int User::UserCount = 0;



}