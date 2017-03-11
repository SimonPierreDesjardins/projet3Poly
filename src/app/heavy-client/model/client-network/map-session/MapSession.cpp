#include "MapSession.h"

#include "NetworkManager.h"
#include "ArbreRendu.h"

namespace client_network
{

MapSession::MapSession(ArbreRendu* tree, NetworkManager* network)
	: entityTree_(tree), network_(network)
{
}

void MapSession::setIsOnlineSession(bool isOnline)
{
	isOnline_ = isOnline;
	// If offline to online, start requesting entity creation.
}

void MapSession::localEntityCreated(NoeudAbstrait* entity)
{
	// If the session is online and the pending queue is empty, send the request now.
	if (isOnline_ && pendingEntityCreationRequests_.empty())
	{
	}
	// If we're offline or other creation requests are already queued,
	// we queue this request.
	else
	{
		pendingEntityCreationRequests_.push(entity);
	}
}

void MapSession::serverEntityCreated(uint8_t type, uint32_t parentId, const glm::vec3& relPos,
	                                  const glm::vec3& absPos, const std::string& userId, uint32_t entityId)
{
	
}

void MapSession::sendEntityCreationRequest(NoeudAbstrait* entity)
{
		// TODO: Refactor data from NoeudAbstrait. 
		glm::vec3 absPos = { entity->obtenirPositionCourante().x,
							 entity->obtenirPositionCourante().y,
							 entity->obtenirPositionCourante().z };

		glm::vec3 relPos = { entity->obtenirPositionRelative().x,
							 entity->obtenirPositionRelative().y,
							 entity->obtenirPositionRelative().z };

		glm::vec3 rotation = { 0.0,
							   0.0,
							   entity->obtenirAngleRotation() };

		glm::vec3 scale = { entity->obtenirFacteurMiseAEchelle(),
							0.0,
							0.0 };

		network_->requestEntityCreation(entity->getType(),
										entity->obtenirParent()->getId(),
										absPos, relPos, rotation, scale);
}

}