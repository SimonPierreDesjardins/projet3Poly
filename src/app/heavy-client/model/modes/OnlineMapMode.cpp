#include "map-session/ClientMapSession.h"

#include "OnlineMapMode.h"

OnlineMapMode::OnlineMapMode(client_network::ClientMapSession* mapSession)
	: mapSession_(mapSession)
{
}

OnlineMapMode::~OnlineMapMode()
{
}

