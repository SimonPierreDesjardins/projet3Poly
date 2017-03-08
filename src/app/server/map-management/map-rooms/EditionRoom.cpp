#include "EditionRoom.h"
#include <iostream>

namespace server
{

void EditionRoom::handleEntityCreationMessage(User* sender, const std::string& message)
{
	if (message.size() != 39)
	{
		std::cout << "Unsupported message " << message << std::endl;
	}
	broadcastMessage(message);
}

}
