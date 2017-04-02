#include <iostream>

#include "MapSession.h"

#include "NetworkManager.h"
#include "ArbreRendu.h"

namespace client_network
{

MapSession::MapSession(ArbreRendu* tree, NetworkManager* network)
	: entityTree_(tree), network_(network)
{
	isOnline_ = network_->isConnected();
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
	entity->setOwnerId(network_->getUserId());
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
	const glm::vec3& absPos, const glm::vec3& relPos,
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	pendingQueueLock_.lock();
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
			PhysicsComponent& physics = newEntity->getPhysicsComponent();
			physics.absolutePosition = { absPos.x, absPos.y, absPos.z };
			physics.relativePosition = { relPos.x, relPos.y, relPos.z };
			physics.rotation = rotation;
			physics.scale = scale;
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
		pendingEntityCreationRequests_.pop();

		confirmedEntities_.insert(std::make_pair(entityId, entityToInsert));
		entityToInsert->setId(entityId);

		// Update entity data.

		PhysicsComponent& physics = entityToInsert->getPhysicsComponent();
		network_->requestEntityPropertyUpdate(entityToInsert->getId(), Networking::ABSOLUTE_POSITION, 
			                                  glm::vec3(physics.absolutePosition));

		network_->requestEntityPropertyUpdate(entityToInsert->getId(), Networking::RELATIVE_POSITION, 
			                                  glm::vec3(physics.relativePosition));

		network_->requestEntityPropertyUpdate(entityToInsert->getId(), Networking::ROTATION, 
			                                  glm::vec3(physics.rotation));

		network_->requestEntityPropertyUpdate(entityToInsert->getId(), Networking::SCALE, 
			                                  glm::vec3(physics.scale));

		network_->requestEntitySelection(entityToInsert->getId(), entityToInsert->estSelectionne());

		auto itParent = confirmedEntities_.find(parentId);
		if (itParent != confirmedEntities_.end())
		{
		}

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
	pendingQueueLock_.unlock();
}

void MapSession::sendEntityCreationRequest(NoeudAbstrait* entity)
{
		PhysicsComponent& physics = entity->getPhysicsComponent();
		NoeudAbstrait* parent = entity->obtenirParent();
		uint32_t parentId = 1;
		if (parent) {
			uint32_t parendId = parent->getId();
		}

		network_->requestEntityCreation(entity->getType(),
										parentId,
										glm::vec3(physics.absolutePosition), glm::vec3(physics.relativePosition), 
			                            glm::vec3(physics.rotation), glm::vec3(physics.scale));
}

void MapSession::deleteLocalEntity(NoeudAbstrait* entity)
{
	pendingQueueLock_.lock();
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
			// Delete locally.
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
	pendingQueueLock_.unlock();
}

void MapSession::serverEntityDeleted(uint32_t entityId)
{
	pendingQueueLock_.lock();
	auto entityIt = confirmedEntities_.find(entityId);
	if (entityIt != confirmedEntities_.end())
	{
		NoeudAbstrait* entityToDelete = entityIt->second;
		entityToDelete->obtenirParent()->effacer(entityToDelete);
		confirmedEntities_.erase(entityIt);
	}
	pendingQueueLock_.unlock();
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

		auto userIt = users_.find(userId);
		if (userIt != users_.end())
		{
			entityIt->second->setSelectionColor(userIt->second.selectionColor);
		}
	}
}

void MapSession::serverEntityPropertyUpdated(uint32_t entityId, Networking::PropertyType type, const glm::vec3& updatedProperty)
{
	pendingQueueLock_.lock();
	auto it = confirmedEntities_.find(entityId);
	if (it != confirmedEntities_.end())
	{
		PhysicsComponent& physics = it->second->getPhysicsComponent();
		switch (type)
		{
		case Networking::ABSOLUTE_POSITION:
			physics.absolutePosition = updatedProperty;
			break;

		case Networking::RELATIVE_POSITION:
			physics.relativePosition = updatedProperty;
			break;

		case Networking::ROTATION:
			physics.rotation = updatedProperty;
			break;

		case Networking::SCALE:
			physics.scale = updatedProperty;
			break;

		case Networking::LINEAR_VELOCITY:
			physics.linearVelocity = updatedProperty;
			break;

		case Networking::ANGULAR_VELOCITY:
			physics.angularVelocity = updatedProperty;
			break;
		}
	}
	pendingQueueLock_.unlock();
}

void MapSession::localEntityPropertyUpdated(NoeudAbstrait* entity, Networking::PropertyType type, const glm::vec3& updatedProperty)
{
	pendingQueueLock_.lock();
	uint32_t entityId = entity->getId();
	if (entityId != 0 && confirmedEntities_.find(entityId) != confirmedEntities_.end())
	{
		network_->requestEntityPropertyUpdate(entity->getId(), (char)(type), updatedProperty);
	}
	pendingQueueLock_.unlock();
}

void MapSession::requestToLeaveMapSession()
{
	if (isOnline_)
	{
		network_->requestToQuitMapSession();
	}
}

void MapSession::serverUserLeftMapSession(uint32_t userId)
{
	// Another user left the room.
	if (userId != network_->getUserId())
	{
		auto it = users_.find(userId);
		if (it != users_.end())
		{
			UserInfo* leavingUser = &it->second;
			selectionColors.push(leavingUser->selectionColor);
			users_.erase(it);
		}
	}
	// I left the room.
	else
	{
		clearMapSession();
	}
}

void MapSession::clearMapSession()
{
	while (!pendingEntityCreationRequests_.empty())
		pendingEntityCreationRequests_.pop();
	confirmedEntities_.clear();
	users_.clear();
	entityTree_->vider();
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