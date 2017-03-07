#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

namespace server
{

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = 0;

	virtual void onReceivedMessage(const std::string& message);
	virtual void onDisconnected(int userId);

	inline int getId() const;

private:
	static int nextObservedId_;
	int id_ = 0;
};

inline int Observer::getId() const
{
	return id_;
}

}

#endif // OBSERVABLE_H
