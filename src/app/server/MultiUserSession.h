#ifndef MULTI_USER_SESSION_H
#define MULTI_USER_SESSION_H

#include "Observer.h"

namespace server
{

class MultiUserSession : public Observer
{
public:
	MultiUserSession();
	virtual ~MultiUserSession() = 0;
	inline int getSessionId() const;

	inline int getId() const;

private:
	static int id_;
};

inline int MultiUserSession::getId() const
{
	return id_;
}

}

#endif // MULTI_USER_SESSION_H
