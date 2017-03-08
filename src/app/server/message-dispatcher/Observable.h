#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <unordered_map>

namespace server
{

class Observer;

class Observable
{
public:
	Observable() = default;
	virtual ~Observable() = 0;

	void dispatchReceivedMessage(const std::string& message);
	void notifyDisconnected(int observableId);

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

private:
	std::unordered_map<char, Observer*> observers_;
};

}

#endif // OBSERVABLE_H