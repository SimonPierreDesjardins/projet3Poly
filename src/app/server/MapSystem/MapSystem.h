#ifndef __MAP_SYSTEM_H
#define __MAP_SYSTEM_H

#include <unordered_map>
#include <memory>

#include "../UserManagement/MultiUserSystem.h"
#include "AbstractMapRoom.h"
#include "Database\MapDatabase.h"
#include "Database\MapFileDatabase.h"

namespace server 
{

class MapEntry 
{
public:
	MapInfo* Info;
	MapFileEntry* File;

	MapEntry(MapInfo* info, MapFileEntry* mapFile);
	void GetSerializedInfo(std::string& message) const;

	void updateSessionType();
	inline AbstractMapRoom* getCurrentSession();

	char getSessionType() const;
	char getNumberOfUsers() const;
	void AddUser(User* user);
	void SendMap(User* user);

private:
	std::unique_ptr<AbstractMapRoom> currentSession_;
};

inline AbstractMapRoom* MapEntry::getCurrentSession()
{
	return currentSession_.get();
}

class MapSystem : public MultiUserSystem
{
public:
	MapSystem(MapInfoDatabase* mapInfoDB, MapFileDatabase* mapFileDB);

protected:
	virtual void TreatUserJoin(User* user);

	virtual void TreatUserMessage(User* user, const std::string& message);

	virtual void TreatUserDisconnect(User* user);

	virtual char GetSystemType();

private:

	char systemType_{ 'm' };

	std::string GetMapListMessage();

	void UpdateUsersMapLists();

	void NotifyMapCreation(const MapEntry& mapEntry);

	void HandleMapCreationMessage(User* user, const std::string& message);

	void HandleMapJoinMessage(User* user, const std::string& message);

	void HandleMapQuitMessage(User* user, const std::string& message);

	void HandleMapDeleteMessage(User* user, const std::string& message);

	void HandleMapRequestMessage(User* user, const std::string& message);
	
	void HandleMapTransferMessage(User* user, const std::string& message);

	void HandleCancelMapTransferMessage(User* user, const std::string& message);

	void HandleMapPermissionChange(User* user, const std::string& message);

	std::unordered_map<unsigned int, MapEntry> _mapList;

	// map json string with users ids as keys to send transfers to the right 
	std::unordered_map<unsigned int, std::string> _mapsInTransfer;

	MapInfoDatabase* _mapInfoDatabase;

	MapFileDatabase* _mapFileDatabase;
};
}

#endif //!__MAP_SYSTEM_H
