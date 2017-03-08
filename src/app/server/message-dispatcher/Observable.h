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

	void addSystemObserver(Observer* observer, char systemType);
	void removeSystemObserver(char systemType);

private:

	typedef std::unordered_map<char, Observer*> ObserversContainer;
	ObserversContainer observers_;
};

}

#endif // OBSERVABLE_H