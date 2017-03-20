#include "NetworkStandard.h"
#include "TypeSerializerDeserializer.h"
#include "../Database/IdGenerator.h"
#include "EditionRoom.h"

#include "MapSystem.h"

namespace server
{



MapEntry::MapEntry(MapInfo* info)
	: Info(info)
{
	updateSessionType();
}

void MapEntry::updateSessionType()
{
	switch (Info->mapType)
	{
	case SIMULATION_MAP:
		// TODO
		break;

	case EDITION_MAP:
		currentSession_ = std::make_unique<EditionRoom>();
		break;
	}
}

void MapEntry::GetSerializedInfo(std::string& message)
{
	Networking::serialize(Info->GetId(), message);
	message.append(1, getSessionType());
	message.append(1, getNumberOfUsers());
	message.append(Info->mapName);
}

char MapEntry::getSessionType()
{
	return Info->mapType;
}

char MapEntry::getNumberOfUsers()
{
	return currentSession_->GetNumberOfUsers();
}

void MapEntry::AddUser(User * user)
{
	currentSession_->AddUser(user);
}

MapSystem::MapSystem(MapInfoDatabase * mapDB)
{
	_mapInfoDatabase = mapDB;


	// populate map entries from DB
	for (auto mapInfo : _mapInfoDatabase->GetElements()) {
		MapEntry newSession(mapInfo.second);
		_mapList.insert({mapInfo.second->GetId(),std::move(newSession)});
	}
}

void MapSystem::TreatUserJoin(User * user)
{
	user->ForwardMessage(GetMapListMessage());
}

void MapSystem::TreatUserMessage(User * user, const std::string & message)
{
	switch (message[Networking::MessageStandard::COMMAND]) {
	case 'c':
		// create map
		HandleMapCreationMessage(user, message);
		break;
	case 'j':
		// join map session
		HandleMapJoinMessage(user, message);
		break;
	case 'd':
		// delete map session
		HandleMapDeleteMessage(user, message);
		break;
	case 'g':
		// get map's graph
		HandleMapGraphRequestMessage(user, message);
		break;
	case 't':
		// forward to map currently constructed by user
		HandleMapTransferMessage(user, message);
		break;
	case 'x':
		// Cancel map transfer
		HandleCancelMapTransferMessage(user, message);
		break;
	case 'p':
		// Change permissions
		HandleMapPermissionChange(user, message);
	}
}

void MapSystem::TreatUserDisconnect(User * user)
{
	// Cancel any transfers the user had going
	HandleCancelMapTransferMessage(user, std::string());
}

char MapSystem::GetSystemType()
{
	return systemType_;
}

std::string MapSystem::GetMapListMessage()
{
	std::string mapListString = "ml";
	// Prevent crash from checking for previous of end() in empty list. 
	if (!_mapList.empty())
	{
		auto last = std::prev(_mapList.end());
		for (auto it = _mapList.begin(); it != _mapList.end(); ++it)
		{
			it->second.GetSerializedInfo(mapListString);
			if (it != last) {
				mapListString += ';';
			}
		}
	}
	return Networking::MessageStandard::AddMessageLengthHeader(mapListString);
}

void MapSystem::UpdateUsersMapLists()
{
	std::string mapListMessage = GetMapListMessage();
	for each (auto systemUser in _connectedUserList) {
		systemUser.second->ForwardMessage(mapListMessage);
	}
}

void MapSystem::NotifyMapCreation(const MapEntry& mapSession)
{
	// Build the message.
	std::string message = "mc";
	message.append(1, mapSession.Info->mapType);
	Networking::serialize(mapSession.Info->GetId(), message);
	message.append(mapSession.Info->mapName);

	// Broadcast.
	broadcastMessage(Networking::MessageStandard::AddMessageLengthHeader(message));
}

void MapSystem::HandleMapCreationMessage(User * user, const std::string & message)
{
	// parse for info
	char type = message[Networking::MessageStandard::DATA_START];
	std::string name = message.substr(Networking::MessageStandard::DATA_START + 1);

	// create map info
	MapInfo* info = new MapInfo();
	info -> mapName = name;
	info -> mapType = type;
	info->Admin = user->Info.GetId();

	// Update database with new info
	_mapInfoDatabase->CreateEntry(info);

	
	MapEntry newSession(info);

	// check if user had map transfer in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		 // Add map data to entry and map JSONDatabase.
		 // destroy map transfer since it is over
		_mapsInTransfer.erase(user->Info.GetId());
	}

	// Get reference before inserting
	MapEntry* map = nullptr;
	auto pair = _mapList.insert({ newSession.Info->GetId(), std::move(newSession) });
	if (pair.second)
	{
		map = &pair.first->second;
		NotifyMapCreation(*map);
	}
}

void MapSystem::HandleMapJoinMessage(User * user, const std::string & message)
{
	unsigned int mapId = Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START);

	auto it = _mapList.find(mapId);
	if (it != _mapList.end())
	{
		// Send joined response.
		std::string response;
		Networking::serialize(uint32_t(14), response);
		response.append("mj");
		Networking::serialize(mapId,response);
		Networking::serialize(user->Info.GetId(), response);
		user->ForwardMessage(response);
		it->second.getCurrentSession()->broadcastMessage(response);

		// Add the user.
		it->second.AddUser(user);
	}
}
void MapSystem::HandleLeaveMapSessionRequest(User* user, const std::string& message)
{
	// Search for the room that contains the user.
	for (auto it = _mapList.begin(); it != _mapList.end(); ++it)
	{
		AbstractMapRoom* currentSession = it->second.getCurrentSession();
		if (currentSession)
		{
			currentSession->RemoveUser(user);
		}
	}
}

void MapSystem::HandleMapDeleteMessage(User * user, const std::string & message)
{
	_mapList.erase(Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START));
}

void MapSystem::HandleMapGraphRequestMessage(User * user, const std::string & message)
{
	// eventually implement start sending the map data
}

void MapSystem::HandleMapTransferMessage(User * user, const std::string & message)
{
	// +4 is to skip the nominator;denominator; in the message
	std::string mapData = message.substr(Networking::MessageStandard::DATA_START + 4);

	// Check if transfer already in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		_mapsInTransfer.at(user->Info.GetId()) += mapData;
	}
	else {
		//create the transfer entry
		_mapsInTransfer.insert({user->Info.GetId(), mapData});
	}
}

void MapSystem::HandleCancelMapTransferMessage(User * user, const std::string & message)
{
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		_mapsInTransfer.erase(user->Info.GetId());
	}
}

void MapSystem::HandleMapPermissionChange(User * user, const std::string & message)
{
	// Eventually manage user permissions
}

}
