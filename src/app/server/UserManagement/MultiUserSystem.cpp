#include "MultiUserSystem.h"

void server::MultiUserSystem::AddUser(User * user)
{
	_userList.insert({ user->Info.UserName, user });
	StartListeningToUser(user);
	TreatUserJoin(user);
}

void server::MultiUserSystem::StartListeningToUser(User * user)
{
	__hook(&User::OnUserDisconnected, user, &MultiUserSystem::OnUserDisconnected);
	__hook(&User::OnUserSentMessage, user, &MultiUserSystem::OnUserMessageReceived);
}

void server::MultiUserSystem::StopListeningToUser(User * user)
{
	__unhook(&User::OnUserDisconnected, user, &MultiUserSystem::OnUserDisconnected);
	__unhook(&User::OnUserSentMessage, user, &MultiUserSystem::OnUserMessageReceived);
}

void server::MultiUserSystem::OnUserDisconnected(User * user)
{
	StopListeningToUser(user);
	_userList.erase(user->Info.UserName);
	TreatUserDisconnect(user);
}

void server::MultiUserSystem::OnUserMessageReceived(User * user, std::string & message)
{
	TreatUserMessage(user, message);
}
