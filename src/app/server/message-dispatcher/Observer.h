#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

namespace server
{

class Observer
{
public:
	Observer(char systemType);
	virtual ~Observer() = 0;

	virtual void onReceivedMessage(const std::string& message);
	virtual void onDisconnected(uint32_t disconnectedUserId);

	inline char getSystemType() const;

private:
	char systemType_;

	Observer() = delete;
};

inline char Observer::getSystemType() const
{
	return systemType_;
}

}

#endif // OBSERVABLE_H
