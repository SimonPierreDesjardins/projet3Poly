#ifndef __MAP_SYSTEM_H
#define __MAP_SYSTEM_H

#include "../UserManagement/MultiUserSystem.h"
#include <unordered_map>
#include <memory>
#include "AbstractMapRoom.h"
#include "Database\MapDatabase.h"

namespace server 
{

class MapEntry 
{
public:
	MapInfo& Info;

	MapEntry(MapInfo& info);
	std::string GetSerializedInfo();

	void updateSessionType();
	inline AbstractMapRoom* getCurrentSession();

	char getSessionType();
	char getNumberOfUsers();
	void AddUser(User* user);

private:
	std::unique_ptr<AbstractMapRoom> currentSession_;
};

inline AbstractMapRoom* MapEntry::getCurrentSession()
{
	return currentSession_.get();
}

class MapSystem : public MultiUserSystem
{
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

	void HandleLeaveMapSessionRequest(User* user, const std::string& message);

	void HandleMapDeleteMessage(User* user, const std::string& message);

	void HandleMapGraphRequestMessage(User* user, const std::string& message);

	void HandleMapTransferMessage(User* user, const std::string& message);

	void HandleCancelMapTransferMessage(User* user, const std::string& message);

	void HandleMapPermissionChange(User* user, const std::string& message);

	std::unordered_map<std::string, MapEntry> _mapList;

	// map json string with users as keys to send transfers to the right 
	std::unordered_map<std::string, std::string> _mapsInTransfer;
};
}

#endif //!__MAP_SYSTEM_H
