#include "NetworkManager.h"

#include "EventHandler.h"

#include "ArbreRendu.h"

namespace event_handler
{

void EventHandler::onEntityCreated(NoeudAbstrait* noeud)
{
	const glm::dvec3& relPos = noeud->obtenirPositionRelative();
	const glm::dvec3& absPos = noeud->obtenirPositionCourante();

	networkManager_->requestEntityCreation(noeud->getId(), noeud->getType(), noeud->obtenirParent()->getId(),
		{ relPos.x, relPos.y, relPos.z }, { absPos.x, absPos.y, absPos.z });
}

void EventHandler::requestEntityCreation(uint32_t entityId, uint8_t type, uint32_t parentId,
	const glm::dvec3& absolutePosition, const glm::dvec3& relativePosition)
{
		
}

}

