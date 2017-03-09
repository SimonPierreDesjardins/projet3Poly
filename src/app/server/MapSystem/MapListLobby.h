#ifndef __MAP_SYSTEM_H
#define __MAP_SYSTEM_H

#include "../UserManagement/MultiUserSystem.h"

namespace server {
	class MapSession {
	public:
		MapSession(std::string mapName, char mapType = 'e');
		MapSession(std::string mapName, std::string mapData, char mapType = 'e');

		std::string GetSerializedInfo();

		std::string Id;
		std::string Name;
		char SessionType;
		char NumberOfUsers = 0;
	};

	class MapSystem:public MultiUserSystem {

	protected:
		virtual void TreatUserJoin(User* user);

		virtual void TreatUserMessage(User* user, std::string& message);

		virtual void TreatUserDisconnect(User* user);

	private:
		std::string GetMapListMessage();

		void UpdateUsersMapLists();

		void HandleMapCreationMessage(User* user, std::string& message);

		void HandleMapJoinMessage(User* user, std::string& message);

		void HandleMapDeleteMessage(User* user, std::string& message);

		void HandleMapGraphRequestMessage(User* user, std::string& message);

		void HandleMapTransferMessage(User* user, std::string& message);

		void HandleCancelMapTransferMessage(User* user, std::string& message);

		void HandleMapPermissionChange(User* user, std::string& message);

		std::map<std::string, MapSession> _mapList;

		// map json string with users as keys to send transfers to the right 
		std::map<std::string, std::string> _mapsInTransfer;


	};
}

#endif //!__MAP_SYSTEM_H
