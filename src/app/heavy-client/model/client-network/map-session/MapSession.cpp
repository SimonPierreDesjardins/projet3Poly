#include "MapSession.h"

#include "NetworkManager.h"
#include "ArbreRendu.h"

namespace client_network
{

MapSession::MapSession(ArbreRendu* tree, NetworkManager* network)
	: entityTree_(tree), network_(network)
{
	confirmedEntities_.insert(std::make_pair(0, entityTree_));
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
		sendEntityCreationRequest(entity);
	}
	pendingEntityCreationRequests_.push(entity);
}

void MapSession::serverEntityCreated(uint8_t type, uint32_t parentId,
	const glm::vec3& relPos, const glm::vec3& absPos,
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	// If this is a new object from another user.
	if (userId != network_->getUserId())
	{
		auto it = confirmedEntities_.find(parentId);
		if (it != confirmedEntities_.end())
		{
			NoeudAbstrait* parent = it->second;
			std::shared_ptr<NoeudAbstrait> newEntity = entityTree_->creerNoeud((EntityType)(type));
			parent->ajouter(newEntity);
			newEntity->assignerPositionCourante({ absPos.x, absPos.y, absPos.z });
			newEntity->assignerPositionRelative({ relPos.x, relPos.y, relPos.z });
			newEntity->assignerAngleRotation(rotation.z);
			newEntity->assignerFacteurMiseAEchelle(scale.x);
			newEntity->setId(entityId);
			confirmedEntities_.insert(std::make_pair(entityId, newEntity.get()));
		}
	}
	// This is a confirmation for the object to be created.
	else
	{
		// Insert server confirmed entity.
		NoeudAbstrait* entityToInsert = pendingEntityCreationRequests_.back();
		pendingEntityCreationRequests_.pop();
		confirmedEntities_.insert(std::make_pair(entityId, entityToInsert));
		entityToInsert->setId(entityId);

		// Send next entity in pending.
		if (!pendingEntityCreationRequests_.empty())
		{
			NoeudAbstrait* entityToConfirm = pendingEntityCreationRequests_.back();
			sendEntityCreationRequest(entityToConfirm);
		}
	}
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