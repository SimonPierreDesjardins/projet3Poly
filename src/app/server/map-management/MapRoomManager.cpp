#include "MapRoomManager.h"

#include "EditionRoom.h"

namespace server
{

MapRoomManager::MapRoomManager()
	: Observer('m')
{
}

MapRoomManager::~MapRoomManager()
{
}

void MapRoomManager::onReceivedMessage(const std::string& message)
{

}

void MapRoomManager::createRoom(RoomType roomType)
{
	switch (roomType)
	{
	case SIMULATION_ROOM:
		rooms_.insert(std::pair<uint32_t, std::unique_ptr<AbstractMapRoom>>(nextRoomId_++, std::unique_ptr<AbstractMapRoom>(new EditionRoom())));
		break;
	// TODO: other room types
	}
}

}