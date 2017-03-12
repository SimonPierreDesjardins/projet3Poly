#ifndef ONLINE_MAP_MODE_H
#define ONLINE_MAP_MODE_H

#include "ModeAbstrait.h"

namespace client_network
{
	class MapSession;
}

class OnlineMapMode : public ModeAbstrait
{
public:
	OnlineMapMode(client_network::MapSession* mapSession);
	virtual ~OnlineMapMode() = 0;

protected:
	client_network::MapSession* mapSession_;

private:
	OnlineMapMode() = delete;
};

#endif // ONLINE_MAP_MODE_H