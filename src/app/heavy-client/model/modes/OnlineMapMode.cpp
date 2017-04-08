#include "MapSession.h"

#include "OnlineMapMode.h"

OnlineMapMode::OnlineMapMode(client_network::MapSession* mapSession)
	: mapSession_(mapSession)
{
	mapSession_->mapReady(this);
}

OnlineMapMode::~OnlineMapMode()
{
}

