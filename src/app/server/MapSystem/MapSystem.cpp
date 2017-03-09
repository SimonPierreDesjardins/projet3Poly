#include "NetworkStandard.h"
#include "../Database/IdGenerator.h"
#include "EditionRoom.h"

#include "MapSystem.h"

server::MapEntry::MapEntry(MapInfo& info)
	: Info(info)
{
}

std::string server::MapEntry::GetSerializedInfo()
{
	return Info.GetId() + ';' + Info.mapName + ';' + getSessionType() + ';' + getNumberOfUsers();
}

char server::MapEntry::getSessionType()
{
	// TODO: Get session type from current session
	return 'e';
}

char server::MapEntry::getNumberOfUsers()
{
	return (currentSession) ? currentSession->GetNumberOfUsers() : 0;
}

void server::MapEntry::AddUser(User * user)
{
	if (!currentSession)
	{
		currentSession = std::make_unique<EditionRoom>();
	}
	currentSession->AddUser(user);
}

void server::MapSystem::TreatUserJoin(User * user)
{
	user->ForwardMessage(GetMapListMessage());
}

void server::MapSystem::TreatUserMessage(User * user, const std::string & message)
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

void server::MapSystem::TreatUserDisconnect(User * user)
{
	// Cancel any transfers the user had going
	HandleCancelMapTransferMessage(user, std::string());
}

char server::MapSystem::GetSystemType()
{
	return systemType_;
}

std::string server::MapSystem::GetMapListMessage()
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

void server::MapSystem::UpdateUsersMapLists()
{
	std::string mapListMessage = GetMapListMessage();
	for each (auto systemUser in _userList) {
		systemUser.second->ForwardMessage(mapListMessage);
	}
}

void server::MapSystem::HandleMapCreationMessage(User * user, const std::string & message)
{
	// parse for info
	std::string data = message.substr(Networking::MessageStandard::DATA_START);
	std::string name = data.substr(0, data.find(';'));
	char type = data[data.size() - 1];

	MapInfo info;
	info.mapName = name;
	MapEntry newSession(std::move(info));

	// check if user had map transfer in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		 // Add map data to entry.
		 // destroy map transfer since it is over
		_mapsInTransfer.erase(user->Info.GetId());
	}

	_mapList.insert({ newSession.Info.GetId(), std::move(newSession) });
}

void server::MapSystem::HandleMapJoinMessage(User * user, const std::string & message)
{
	std::string mapId = message.substr(Networking::MessageStandard::DATA_START);

	auto it = _mapList.find(mapId);
	if (it != _mapList.end())
	{
		it->second.AddUser(user);
	}
}
void server::MapSystem::HandleLeaveMapSessionRequest(User* user, const std::string& message)
{
	for (auto it = _mapList.begin(); it != _mapList.end(); ++it)
	{
		AbstractMapRoom* currentSession = it->second.currentSession.get();
		if (currentSession)
		{
			currentSession->RemoveUser(user);
		}
	}
}

void server::MapSystem::HandleMapDeleteMessage(User * user, const std::string & message)
{
	_mapList.erase(message.substr(Networking::MessageStandard::DATA_START));
}

void server::MapSystem::HandleMapGraphRequestMessage(User * user, const std::string & message)
{
	// eventually implement start sending the map data
}

void server::MapSystem::HandleMapTransferMessage(User * user, const std::string & message)
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

void server::MapSystem::HandleCancelMapTransferMessage(User * user, const std::string & message)
{
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		_mapsInTransfer.erase(user->Info.GetId());
	}
}

void server::MapSystem::HandleMapPermissionChange(User * user, const std::string & message)
{
	// Eventually manage user permissions
}
