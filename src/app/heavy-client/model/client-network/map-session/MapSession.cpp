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
	selectionColors.push({ 1.0, 1.0, 0.0, 1.0 });
	selectionColors.push({ 0.5, 0.0, 1.0, 1.0 });
	selectionColors.push({ 0.0, 0.75, 1.0, 1.0 });
	selectionColors.push({ 1.0, 0.2, 0.0, 1.0 });
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
	// If this is a new object from another user.
	if (userId != network_->getUserId())
	{
		auto itParent = confirmedEntities_.find(parentId);
		// If the parent and the user are found
		if (itParent != confirmedEntities_.end())
		{
			NoeudAbstrait* parent = itParent->second;
			std::shared_ptr<NoeudAbstrait> newEntity = entityTree_->creerNoeud((EntityType)(type));
			parent->ajouter(newEntity);
			newEntity->assignerPositionCourante({ absPos.x, absPos.y, absPos.z });
			newEntity->assignerPositionRelative({ relPos.x, relPos.y, relPos.z });
			newEntity->assignerAngleRotation(rotation.z);
			newEntity->assignerFacteurMiseAEchelle(scale.x);
			newEntity->setId(entityId);

			auto userIt = users_.find(userId);
			if (userIt != users_.end())
			{
				newEntity->setSelectionColor(userIt->second.selectionColor);
				newEntity->setOwnerId(userId);
				newEntity->assignerSelection(true);
			}

			newEntity->setOwnerId(userId);
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

		pendingQueueLock_.lock();
		pendingEntityCreationRequests_.pop();
		pendingQueueLock_.unlock();

		confirmedEntities_.insert(std::make_pair(entityId, entityToInsert));
		entityToInsert->setId(entityId);

		// Update entity data.
		network_->requestEntitySelection(entityToInsert->getId(), entityToInsert->estSelectionne());

		// Update selection color.
		auto userIt = users_.find(userId);
		if (userIt != users_.end())
		{
			entityToInsert->setSelectionColor(userIt->second.selectionColor);
		}

		std::cout << "Local entity creation confirmed : " << entityToInsert->obtenirNom() <<
			" id : " << entityToInsert->getId() << " parentid : " << entityToInsert->obtenirParent()->getId() << std::endl;

		// Send next entity in pending.
		NoeudAbstrait* entityToConfirm = nullptr;

		if (!pendingEntityCreationRequests_.empty())
		{
			entityToConfirm = pendingEntityCreationRequests_.front();
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

		std::cout << "Local entity creation request sent : " << entity->obtenirNom() <<
			" id : " << entity->getId() << " parentid : " << entity->obtenirParent()->getId() << std::endl;

		network_->requestEntityCreation(entity->getType(),
										entity->obtenirParent()->getId(),
										absPos, relPos, rotation, scale);
}

void MapSession::deleteLocalEntity(NoeudAbstrait* entity)
{
	std::stack<NoeudAbstrait*> toDeleteStack;
	toDeleteStack.push(entity);

	while (!toDeleteStack.empty())
	{
		NoeudAbstrait* todelete = toDeleteStack.top();
		int nEnfant = todelete->obtenirNombreEnfants();
		// If the node has no child.
		if (!nEnfant)
		{
			// If the entity exists on the server, notify the server.
			if (todelete->getId() != 0)
			{
				confirmedEntities_.erase(todelete->getId());
				network_->requestEntityRemoval(todelete->getId());
			}
			// Delete from locally.
			toDeleteStack.pop();
			todelete->obtenirParent()->effacer(todelete);
		}
		// If the top node has children, push them in the stack.
		else
		{
			for	(int i = 0; i < todelete->obtenirNombreEnfants(); ++i)
			{
				toDeleteStack.push(todelete->chercher(i));
			}
		}
	}
}

void MapSession::serverEntityDeleted(uint32_t entityId)
{
	auto entityIt = confirmedEntities_.find(entityId);
	if (entityIt != confirmedEntities_.end())
	{
		NoeudAbstrait* entityToDelete = entityIt->second;
		entityToDelete->obtenirParent()->effacer(entityToDelete);
		confirmedEntities_.erase(entityIt);
	}
}

void MapSession::updateSelectionStateLocalEntityAndChildren(NoeudAbstrait* entity, bool isSelected)
{
	std::queue<NoeudAbstrait*> selectionQueue;
	selectionQueue.push(entity);
	while (!selectionQueue.empty())
	{
		// Get the next in the queue and send it.
		NoeudAbstrait* toSelect = selectionQueue.front();
		selectionQueue.pop();

		uint32_t entityId = toSelect->getId();
		auto entityIt = confirmedEntities_.find(entityId);
		if (entityIt != confirmedEntities_.end())
		{
			network_->requestEntitySelection(entityId, isSelected);
		}

		// Push children in the queue.
		uint32_t nChildren = toSelect->obtenirNombreEnfants();
		for (int i = 0; i < nChildren; ++i)
		{
			selectionQueue.push(toSelect->chercher(i));
		}
	}
}

void MapSession::serverEntitySelected(uint32_t entityId, bool isSelected, uint32_t userId)
{
	auto entityIt = confirmedEntities_.find(entityId);
	if (entityIt != confirmedEntities_.end())
	{
		entityIt->second->setOwnerId(userId);
		entityIt->second->assignerSelection(isSelected);
	}
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

void MapSession::addUser(uint32_t userId, const std::string& userName)
{
	if (!selectionColors.empty())
	{
		UserInfo newUser;
		newUser.userId = userId;
		newUser.userName = userName;
		newUser.selectionColor = selectionColors.top();
		selectionColors.pop();
		users_.insert(std::make_pair(userId, newUser));
	}
}

void MapSession::removeUser(uint32_t userId)
{
	auto it = users_.find(userId);
	if (it != users_.end())
	{
		selectionColors.push(it->second.selectionColor);
		users_.erase(it);
	}
}

void MapSession::clearUsers()
{
	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		selectionColors.push(it->second.selectionColor);
		users_.erase(it);
	}
}

}