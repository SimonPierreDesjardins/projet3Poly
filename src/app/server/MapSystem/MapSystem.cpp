#include "NetworkStandard.h"
#include "TypeSerializerDeserializer.h"
#include "../Database/IdGenerator.h"
#include "EditionRoom.h"

#include "MapSystem.h"

namespace server
{



MapEntry::MapEntry(MapInfo& info)
	: Info(info)
{
	updateSessionType();
}

void MapEntry::updateSessionType()
{
	switch (Info.mapType)
	{
	case SIMULATION_MAP:
		// TODO
		break;

	case EDITION_MAP:
		currentSession_ = std::make_unique<EditionRoom>();
		break;
	}
}

std::string MapEntry::GetSerializedInfo()
{
	return Info.GetId() + ';' + Info.mapName + ';' + getSessionType() + ';' + getNumberOfUsers();
}

char MapEntry::getSessionType()
{
	return Info.mapType;
}

char MapEntry::getNumberOfUsers()
{
	return currentSession_->GetNumberOfUsers();
}

void MapEntry::AddUser(User * user)
{
	currentSession_->AddUser(user);
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
			mapListString += it->second.GetSerializedInfo();
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
	for each (auto systemUser in _userList) {
		systemUser.second->ForwardMessage(mapListMessage);
	}
}

void MapSystem::NotifyMapCreation(const MapEntry& mapSession)
{
	// Compute message size.
	size_t messageSize = mapSession.Info.mapName.size() +  
		                 mapSession.Info.GetId().size() + 3;
	// Build the message.
	std::string message;
	Networking::serialize((uint32_t)(messageSize), message);

	message.append("mc");
	message.append(1, mapSession.Info.mapType);
	message.append(mapSession.Info.GetId());
	message.append(mapSession.Info.mapName);

	// Broadcast.
	broadcastMessage(message);
}

void MapSystem::HandleMapCreationMessage(User * user, const std::string & message)
{
	// parse for info
	char type = message[Networking::MessageStandard::DATA_START];
	std::string name = message.substr(Networking::MessageStandard::DATA_START + 1);

	MapInfo info;
	info.mapName = name;
	info.mapType = type;
	MapEntry newSession(std::move(info));

	// check if user had map transfer in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		 // Add map data to entry.
		 // destroy map transfer since it is over
		_mapsInTransfer.erase(user->Info.GetId());
	}

	// Get reference before inserting
	MapEntry* map = nullptr;
	auto pair = _mapList.insert({ newSession.Info.GetId(), std::move(newSession) });
	if (pair.second)
	{
		map = &pair.first->second;
		NotifyMapCreation(*map);
	}
}

void MapSystem::HandleMapJoinMessage(User * user, const std::string & message)
{
	std::string mapId = message.substr(Networking::MessageStandard::DATA_START);
	auto it = _mapList.find(mapId);
	if (it != _mapList.end())
	{
		// Send joined response.
		std::string response(message);
		response.append(user->Info.GetId());
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
	_mapList.erase(message.substr(Networking::MessageStandard::DATA_START));
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
