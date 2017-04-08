#include <iostream>

#include "MapSession.h"

#include "NetworkManager.h"
#include "ArbreRendu.h"

namespace engine
{

	MapSession::MapSession(ArbreRendu* tree)
		: entityTree_(tree)
	{
	}

}