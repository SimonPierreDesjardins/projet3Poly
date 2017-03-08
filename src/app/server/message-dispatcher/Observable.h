#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>

namespace server
{

class Observer;
class User;

class Observable
{
public:
	Observable() = default;
	virtual ~Observable() = 0;

	void dispatchReceivedMessage(User* sender, const std::string& message);
	void notifyDisconnected(User* disconnectedUser);

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

private:
	std::unordered_map<char, Observer*> observers_;
};

}

#endif // OBSERVABLE_H