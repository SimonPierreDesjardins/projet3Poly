#ifndef ONLINE_MODE_H
#define ONLINE_MODE_H

#include "ModeAbstrait.h"

class OnlineMode : public ModeAbstrait
{
public:
	OnlineMode() = default;
	virtual ~OnlineMode() = 0;

};


#endif // ONLINE_MODE_H