#ifndef ONLINE_MAP_MODE_H
#define ONLINE_MAP_MODE_H

#include "ModeAbstrait.h"

namespace client_network
{
	class ClientMapSession;
}

class OnlineMapMode : public ModeAbstrait
{
public:
	OnlineMapMode(client_network::ClientMapSession* mapSession);
	virtual ~OnlineMapMode() = 0;

protected:
	client_network::ClientMapSession* mapSession_;

private:
	OnlineMapMode() = delete;
};

#endif // ONLINE_MAP_MODE_H