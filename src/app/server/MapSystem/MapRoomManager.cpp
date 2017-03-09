#include <cassert>

#include "EditionRoom.h"

#include "MapRoomManager.h"
#include <iostream>

namespace server
{

MapRoomManager::~MapRoomManager()
{
}

void MapRoomManager::postAddUser(User* user)
{
	user->addSystemObserver(this, MAP_MESSAGE);
}

void MapRoomManager::postRemoveUser(User* user)
{
	user->removeSystemObserver(MAP_MESSAGE);
}

void MapRoomManager::handleJoinMapSessionRequest(User* sender, const std::string& message)
{
	assert(message.size() == 10);

	std::string serializedMapId = message.substr(6, message.size() - 6);
	uint32_t const* p = reinterpret_cast<const uint32_t*>(serializedMapId.c_str());
	const uint32_t mapId = *p;

	std::unordered_map<uint32_t, std::unique_ptr<AbstractMapRoom>>::iterator it = rooms_.find(mapId);
	if (it != rooms_.end())
	{
		it->second->addUser(sender);
		roomsByUserId_.insert(std::pair<uint32_t, AbstractMapRoom*>(sender->info_.id_, it->second.get()));
	}
}

void MapRoomManager::handleLeaveMapSessionRequest(User* sender, const std::string& message)
{
	assert(message.size() == 6);

	uint32_t userId = sender->info_.id_;
	std::unordered_map<uint32_t, AbstractMapRoom*>::iterator it = roomsByUserId_.find(userId);
	if (it != roomsByUserId_.end())
	{
		it->second->removeUser(sender);
		roomsByUserId_.erase(userId);
	}
}

void MapRoomManager::onReceivedMessage(User* sender, const std::string& message)
{
	assert(message[4] == 'm');

	switch (message[5])
	{
	case 'j':
		handleJoinMapSessionRequest(sender, message);
		break;

	case 'l':
		handleLeaveMapSessionRequest(sender, message);
		break;

	// TODO: Handle other message types here.

	}
}

void MapRoomManager::onDisconnected(User* disconnectedUser)
{
	uint32_t userId = disconnectedUser->info_.id_;
	// Also remove the user in the room.
	users_.erase(userId);
	roomsByUserId_.erase(userId);
}

void MapRoomManager::createRoom(RoomType roomType)
{
	switch (roomType)
	{
	case EDITION_ROOM:
		rooms_.insert(std::pair<uint32_t, std::unique_ptr<AbstractMapRoom>>(nextRoomId_++, std::unique_ptr<AbstractMapRoom>(new EditionRoom())));
		break;

	// TODO: other room types
	}
}
void MapRoomManager::removeRoom(uint32_t roomId)
{
	rooms_.erase(roomId);
}

}