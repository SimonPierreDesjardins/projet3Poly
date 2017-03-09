#ifndef __MAP_EDITING_SESSION_H
#define __MAP_EDITING_SESSION_H

#include "../UserManagement/MultiUserSystem.h"

namespace server {
	class MapEditingSession:public MultiUserSystem {

		virtual void TreatUserJoin(User* user);

		virtual void TreatUserMessage(User* user, std::string& string);

		virtual void TreatUserDisconnect(User* user);
	};
}

#endif // !__MAP_EDITING_SESSION_H
