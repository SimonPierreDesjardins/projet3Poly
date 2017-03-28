#ifndef SIMULATION_ROOM_H
#define SIMULATION_ROOM_H

#include "AbstractMapRoom.h"

namespace server
{

class SimulationRoom : public AbstractMapRoom
{
public:
	SimulationRoom(MapInfo* mapInfo);
	virtual ~SimulationRoom() = default;
};

}

#endif // SIMULATION_ROOM_H
