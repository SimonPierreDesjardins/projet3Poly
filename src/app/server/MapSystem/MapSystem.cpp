#include "NetworkStandard.h"
#include "TypeSerializerDeserializer.h"
#include "../Database/IdGenerator.h"
#include "EditionRoom.h"

#include "MapSystem.h"

namespace server
{

MapEntry::MapEntry(MapInfo* info, MapFileEntry* mapFile)
	: Info(info), File(mapFile)
{
	updateSessionType();
}

void MapEntry::updateSessionType()
{
	switch (Info->mapType)
	{
	case SIMULATION_MAP:
		currentSession_ = std::make_unique<EditionRoom>(Info, File);
		break;

	case EDITION_MAP:
		currentSession_ = std::make_unique<EditionRoom>(Info, File);
		break;
	}
}

void MapEntry::GetSerializedInfo(std::string& message) const
{
	Networking::serialize(Info->GetId(), message);
	message.append(1, getSessionType());
	message.append(1, getNumberOfUsers());
	message.append(1, Info->isPrivate ? 0x01:0x00);
	Networking::serialize(Info->Admin, message);
	message.append(Info->mapName);
}

char MapEntry::getSessionType() const
{
	return Info->mapType;
}

char MapEntry::getNumberOfUsers() const
{
	return currentSession_->GetNumberOfUsers();
}

void MapEntry::AddUser(User * user)
{
	currentSession_->AddUser(user);
}

void MapEntry::SendMap(User * user)
{
	std::thread([this, user]() {
		// open file
		std::string mapFile = File->MapData;

		// start reading through the memblock, segmenting into packets and sending them

		std::vector<std::string> packets;

		int maxPacketSize = 256;
		int bytesLeft = mapFile.size();
		int currentByte = 0;

		while (bytesLeft > 0) {
			// add to an array of messages to send;
			auto packetSize = (maxPacketSize < bytesLeft) ? maxPacketSize : bytesLeft;
			packets.push_back(std::move(mapFile.substr(currentByte, packetSize)));
			currentByte += packetSize;
			bytesLeft -= packetSize;
		}

		char numberOfPackets = packets.size();
		for (char i = 0; i < numberOfPackets; ++i) {
			std::string message("mt");
			message += i + 1;
			message += numberOfPackets;
			message += packets[i];
			user->ForwardMessage(Networking::MessageStandard::AddMessageLengthHeader(message));
		}
	}).detach();
}

MapSystem::MapSystem(MapInfoDatabase * mapInfoDB, MapFileDatabase * mapFileDB)
{
	_mapInfoDatabase = mapInfoDB;

	_mapFileDatabase = mapFileDB;


	// populate map entries from DB
	for (auto mapInfo : _mapInfoDatabase->GetElements()) {
		// find associated map file in db
		MapEntry newSession(mapInfo.second, mapFileDB->GetElements()[mapInfo.second->MapId]);
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

	case 'q':
		// Quit map session
		HandleMapQuitMessage(user, message);
		break;

	case 'd':
		// delete map session
		HandleMapDeleteMessage(user, message);
		break;

	case 'f':
		// get map's graph
		HandleMapRequestMessage(user, message);
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
		break;
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
	mapSession.GetSerializedInfo(message);

	// Broadcast.
	broadcastMessage(Networking::MessageStandard::AddMessageLengthHeader(message));
}

void MapSystem::HandleMapCreationMessage(User * user, const std::string & message)
{
	// parse for info
	char type = message[Networking::MessageStandard::DATA_START];
	char isPrivate = message[Networking::MessageStandard::DATA_START + 1];

	std::string name("");
	std::string password("");
	// if map is private, then we have to get the password too, otherwise, no need
	if (isPrivate) {
		auto namePos = Networking::MessageStandard::DATA_START + 2;
		auto seperatorPos = message.find(';');
		name.append(message.substr(namePos, seperatorPos - namePos));
		password.append(message.substr(seperatorPos + 1));
	}
	else{
		name.append(message.substr(Networking::MessageStandard::DATA_START + 2));
	}


	// create map file reference
	MapFileEntry* mapFile = new MapFileEntry();

	// check if user had map transfer in progress
	if (_mapsInTransfer.count(user->Info.GetId()) > 0) {
		// Add map data to entry and map JSONDatabase.
		mapFile->MapData = std::move(_mapsInTransfer.at(user->Info.GetId()));
		// destroy map transfer since it is over
		_mapsInTransfer.erase(user->Info.GetId());
	}
	else {
		//load default map?
	}

	// create map info
	MapInfo* info = new MapInfo();
	info -> mapName = name;
	info -> mapType = type;
	info->isPrivate = isPrivate != 0;
	info->password = password;
	info->Admin = user->Info.GetId();
	info->MapId = mapFile->GetId();

	// Update database with new info
	_mapInfoDatabase->CreateEntry(info);
	_mapFileDatabase->CreateEntry(mapFile);

	// update user with this map as its created map
	user->Info.CreatedMaps.insert(info->GetId());

	MapEntry newSession(info, mapFile);

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

	auto mapIt = _mapList.find(mapId);
	if (mapIt != _mapList.end())
	{

		// prepare response
		std::string response("mjs");
		Networking::serialize(mapId, response);
		Networking::serialize(user->Info.GetId(), response);
		response.append(user->Info.UserName);
		response = Networking::MessageStandard::AddMessageLengthHeader(response);

		// check if map is private
		if (mapIt->second.Info->isPrivate) {
			// get password from message after the join Id
			std::string password = message.substr(Networking::MessageStandard::DATA_START + 4);
			if (password != mapIt->second.Info->password) {
				// send error message
				response[10] = 'd';
				user->ForwardMessage(response);
				return;
			}
		}

		user->ForwardMessage(response);

		mapIt->second.AddUser(user);



		// Adjust user stats according to map joined
		switch (mapIt->second.getSessionType()) {
		case 1 /* Simulation */:
			user->Info.NumberOfSimulations++;
			break;
		case 2 /* Edition */ :
			user->Info.ModifiedMaps.insert(mapIt->second.Info->GetId());
			break;
		}
	}
}
void MapSystem::HandleMapQuitMessage(User* user, const std::string& message)
{
	// Search for the room that contains the user.
	bool isMapSessionFound = false;
	AbstractMapRoom* foundMapSession = nullptr;

	// There should only be one map session found.
	for (auto it = _mapList.begin(); it != _mapList.end() && !isMapSessionFound; ++it)
	{
		AbstractMapRoom* mapSession = it->second.getCurrentSession();
		if (mapSession)
		{
			isMapSessionFound = mapSession->RemoveUser(user);
			foundMapSession = mapSession;
		}
	}

	// Send Reply to every user in the mapSession.
	std::string reply(message);
	Networking::serialize(user->Info.GetId(), reply);
	Networking::MessageStandard::UpdateLengthHeader(reply);
	foundMapSession->broadcastMessage(reply);
}

void MapSystem::HandleMapDeleteMessage(User * user, const std::string & message)
{
	unsigned int mapId = Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START);
	
	// update the user's created maps 
	user->Info.CreatedMaps.erase(mapId);

	_mapList.erase(Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START));
}

void MapSystem::HandleMapRequestMessage(User * user, const std::string & message)
{
	// eventually implement start sending the map data
	unsigned int mapId = Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START);

	_mapList.at(mapId).SendMap(user);
}

void MapSystem::HandleMapTransferMessage(User * user, const std::string & message)
{
	// +2 is to skip the nominator;denominator; in the message
	std::string mapData = message.substr(Networking::MessageStandard::DATA_START + 2);

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
	unsigned int mapId = Networking::deserializeInteger(message.c_str() + Networking::MessageStandard::DATA_START);

	auto mapKvp = _mapList.find(mapId);
	if (mapKvp != _mapList.end()) {
		
		//start building reply message
		std::string reply = Networking::MessageStandard::AddMessageLengthHeader(message.substr(Networking::MessageStandard::SYSTEM, 7));

		// check if user is admin
		if (mapKvp->second.Info->Admin != user->Info.GetId()) {

			// change result char to error
			reply[Networking::MessageStandard::DATA_START + 4] = 'd';

			// send error
			user->ForwardMessage(reply);
			return;
		}
		
		char permission = message[Networking::MessageStandard::DATA_START + 4];
		mapKvp->second.Info->isPrivate = (permission == 'c');
		// set password if necessary
		if (permission == 'c') {
			mapKvp -> second.Info->password = message.substr(Networking::MessageStandard::DATA_START + 5);
		}

		// tell user everything went as planned
		user->ForwardMessage(reply);
	}
}

}