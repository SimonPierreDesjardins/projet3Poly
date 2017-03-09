#include "MapListLobby.h"
#include "NetworkStandard.h"
#include "../Database/IdGenerator.h"

server::MapSession::MapSession(std::string mapName, char type):
	Name(mapName),
	Id(server::IdGenerator::GenerateId()),
	SessionType(type)
{
}

server::MapSession::MapSession(std::string mapName, std::string mapData, char mapType):MapSession(mapName, mapType)
{	
	// create map graph from string mapData
}

std::string server::MapSession::GetSerializedInfo()
{
	return Id + ';' + Name + ';' + SessionType + ';' + NumberOfUsers;
}

void server::MapSystem::TreatUserJoin(User * user)
{
	user->ForwardMessage(GetMapListMessage());
}

void server::MapSystem::TreatUserMessage(User * user, std::string & message)
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

std::string server::MapSystem::GetMapListMessage()
{
	std::string mapListString = "ml";
	int count = _mapList.size();
	int current = 0;

	for each(auto mapIdPair in _mapList) {
		mapListString += mapIdPair.second.GetSerializedInfo();
		if (current < count - 1) {
			mapListString += ';';
		}
		current++;
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

void server::MapSystem::HandleMapCreationMessage(User * user, std::string & message)
{
	// parse for info
	std::string data = message.substr(Networking::MessageStandard::DATA_START);
	std::string name = data.substr(0, data.find(';'));
	char type = data[data.size() - 1];

	// check if user had map transfer in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		// create map entry from map data
		MapSession newSession(std::move(name), _mapsInTransfer.at(user->Info.GetId()), std::move(type));
		_mapList.insert({ newSession.Id, std::move(newSession) });

		// destroy map transfer since it is over
		_mapsInTransfer.erase(user->Info.GetId());
		
	}
	else {
		// create map from scratch
		MapSession newSession(std::move(name), std::move(type));
		_mapList.insert({ newSession.Id, std::move(newSession) });
	}

}

void server::MapSystem::HandleMapJoinMessage(User * user, std::string & message)
{
	// insert map session joining logic here
}

void server::MapSystem::HandleMapDeleteMessage(User * user, std::string & message)
{
	_mapList.erase(message.substr(Networking::MessageStandard::DATA_START));
}

void server::MapSystem::HandleMapGraphRequestMessage(User * user, std::string & message)
{
	// eventually implement start sending the map data
}

void server::MapSystem::HandleMapTransferMessage(User * user, std::string & message)
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

void server::MapSystem::HandleCancelMapTransferMessage(User * user, std::string & message)
{
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		_mapsInTransfer.erase(user->Info.GetId());
	}
}

void server::MapSystem::HandleMapPermissionChange(User * user, std::string & message)
{
	// Eventually manage user permissions
}
