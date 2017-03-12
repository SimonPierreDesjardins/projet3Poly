#ifndef __CHAT_SYSTEM_H
#define __CHAT_SYSTEM_H

#include "../UserManagement/MultiUserSystem.h"

namespace server {
	

	class ChatSystem:public MultiUserSystem {
	public:
		///<summary>Starts up the chat system and creates the general channel</summary>
		ChatSystem();

	protected:

		virtual char GetSystemType();

		virtual void TreatUserJoin(User* user);

		virtual void TreatUserMessage(User* user, const std::string& message);

		virtual void TreatUserDisconnect(User* user);

	private:
		class ChatSession {
		public:
			ChatSession(std::string name);

			///<summary> This chat session's name</summary>
			std::string Name;

			///<summary> Gets the list of users seperated by semicolons</summary>
			std::string GetUserList();

			///<summary> Adds a user to the list of users in this chat</summary>
			///<summary> Returns true if operation performed</summary>
			bool AddUser(User*);

			///<summary> Removes the user from this session</summary>
			///<summary> Returns true if operation performed</summary>
			bool RemoveUser(User*);

			std::vector<User*> UserList;
		};

		char _systemType{ 'c' };

		std::string GetChannelList();

		void ParseUserJoinRequest(User* user, const std::string& message);

		void ParseUserLeaveRequest(User* user, const std::string& message);

		void AddUserToChannel(User* user, const std::string& channelName);

		void RemoveUserFromChannel(User* user, const std::string& channelName);

		void BroadcastUserList(std::string channelName);
		
		std::unordered_map<std::string, ChatSession> _chatSessions;
	};
}

#endif //!__CHAT_SYSTEM_H
