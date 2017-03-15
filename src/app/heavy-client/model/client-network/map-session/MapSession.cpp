#include <iostream>

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
	pendingQueueLock_.lock();
	std::cout << "Local entity created : " << entity->obtenirNom() << " id : " << entity->getId() 
		<< " parent : " << entity->obtenirParent()->obtenirNom() << " id : " << entity->obtenirParent()->getId() << std::endl;
	std::cout << "Queue size is " << pendingEntityCreationRequests_.size() << std::endl;
	// If the session is online and the pending queue is empty, send the request now.
	if (isOnline_ && pendingEntityCreationRequests_.empty())
	{
		std::cout << "Local EntityQueue is empty, sending creation request right now." << std::endl;
		sendEntityCreationRequest(entity);
	}
	pendingEntityCreationRequests_.push(entity);
	pendingQueueLock_.unlock();
}

void MapSession::serverEntityCreated(uint8_t type, uint32_t parentId,
	const glm::vec3& relPos, const glm::vec3& absPos,
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	pendingQueueLock_.lock();
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
			std::cout << "Server entity created : " << newEntity->obtenirNom() <<
				" id : " << newEntity->getId() << " parentid : " << parent->getId() << std::endl;
		}
	}
	// This is a confirmation for the object to be created.
	else
	{
		// Insert server confirmed entity.
		NoeudAbstrait* entityToInsert = pendingEntityCreationRequests_.front();
		pendingEntityCreationRequests_.pop();
		confirmedEntities_.insert(std::make_pair(entityId, entityToInsert));
		entityToInsert->setId(entityId);

		std::cout << "Local entity creation confirmed : " << entityToInsert->obtenirNom() <<
			" id : " << entityToInsert->getId() << " parentid : " << entityToInsert->obtenirParent()->getId() << std::endl;

		// Send next entity in pending.
		if (!pendingEntityCreationRequests_.empty())
		{
			NoeudAbstrait* entityToConfirm = pendingEntityCreationRequests_.front();
			sendEntityCreationRequest(entityToConfirm);
		}
	}
	pendingQueueLock_.unlock();
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

		std::cout << "Local entity creation request sent : " << entity->obtenirNom() <<
			" id : " << entity->getId() << " parentid : " << entity->obtenirParent()->getId() << std::endl;

		network_->requestEntityCreation(entity->getType(),
										entity->obtenirParent()->getId(),
										absPos, relPos, rotation, scale);
}

void MapSession::serverEntityPropertyUpdated(uint32_t entityId, Networking::PropertyType type, const glm::vec3& updatedProperty)
{
	auto it = confirmedEntities_.find(entityId);
	if (it != confirmedEntities_.end())
	{
		switch (type)
		{
		case Networking::ABSOLUTE_POSITION:
			it->second->assignerPositionCourante({ updatedProperty.x, updatedProperty.y, updatedProperty.z });
			break;

		case Networking::RELATIVE_POSITION:
			it->second->assignerPositionRelative({ updatedProperty.x, updatedProperty.y, updatedProperty.z });
			break;

		case Networking::ROTATION:
			it->second->assignerAngleRotation(updatedProperty.z);
			break;

		case Networking::SCALE:
			it->second->assignerFacteurMiseAEchelle(updatedProperty.x);
			break;

		case Networking::LINEAR_VELOCITY:
			// TODO
			break;

		case Networking::ANGULAR_VELOCITY:
			// TODO
			break;
		}
	}
}

void MapSession::localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType type, const glm::vec3& updatedProperty)
{
	network_->requestEntityPropertyUpdate(entity->getId(), (char)(type), updatedProperty);
}

}