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

void MapSession::createServerEntity(const PhysicsComponent& properties, uint8_t type, uint32_t entityId, uint32_t parentId, uint32_t userId)
{
	auto itParent = confirmedEntities_.find(parentId);
	// If the parent is not found, we return.
	if (itParent == confirmedEntities_.end()) return;

	NoeudAbstrait* parent = itParent->second;
	std::shared_ptr<NoeudAbstrait> newEntity = entityTree_->creerNoeud((EntityType)(type));
	if (!newEntity) return;
	parent->ajouter(newEntity);
	PhysicsComponent& physics = newEntity->getPhysicsComponent();
	physics.absolutePosition = properties.absolutePosition;
	physics.relativePosition = properties.relativePosition;
	physics.rotation = properties.rotation;
	physics.scale = properties.scale;
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

void MapSession::confirmLocalEntity(NoeudAbstrait* entityToConfirm, uint32_t entityId)
{
	if (!entityToConfirm) return;

	confirmedEntities_.insert(std::make_pair(entityId, entityToConfirm));
	entityToConfirm->setId(entityId);

	// Update entity data.
	PhysicsComponent& physics = entityToConfirm->getPhysicsComponent();
	network_->requestEntityPropertyUpdate(entityToConfirm->getId(), Networking::ABSOLUTE_POSITION, 
										  glm::vec3(physics.absolutePosition));

	network_->requestEntityPropertyUpdate(entityToConfirm->getId(), Networking::RELATIVE_POSITION, 
										  glm::vec3(physics.relativePosition));

	network_->requestEntityPropertyUpdate(entityToConfirm->getId(), Networking::ROTATION, 
										  glm::vec3(physics.rotation));

	network_->requestEntityPropertyUpdate(entityToConfirm->getId(), Networking::SCALE, 
										  glm::vec3(physics.scale));

	network_->requestEntitySelection(entityToConfirm->getId(), entityToConfirm->estSelectionne());

	// Update selection color.
	auto userIt = users_.find(network_->getUserId());
	if (userIt != users_.end())
	{
		entityToConfirm->setSelectionColor(userIt->second.selectionColor);
	}

	// Send next entity to confirm.
	if (!pendingEntityCreationRequests_.empty())
	{
		NoeudAbstrait* entityToConfirm = pendingEntityCreationRequests_.front();
		sendEntityCreationRequest(entityToConfirm);
	}

	std::cout << "Local entity creation confirmed : " << entityToConfirm->obtenirNom() <<
		" id : " << entityToConfirm->getId() << " parentid : " << entityToConfirm->obtenirParent()->getId() << std::endl;
}

void MapSession::serverEntityCreated(uint8_t type, uint32_t parentId,
	const glm::vec3& absPos, const glm::vec3& relPos,
	const glm::vec3& rotation, const glm::vec3& scale,
	uint32_t entityId, uint32_t userId)
{
	PhysicsComponent properties;
	properties.absolutePosition = absPos;
	properties.relativePosition = relPos;
	properties.rotation = rotation;
	properties.scale = scale;

	std::cout << "Server entity creation message from server : " <<
		" id : " << entityId << "owner id : " << userId << " my id: " << network_->getUserId() << std::endl;

	pendingQueueLock_.lock();
	// If this is a new object from another user.
	if (userId != network_->getUserId())
	{
		createServerEntity(properties, type, entityId, parentId, userId);
	}
	// User id is mine so it might be a confirmation.
	else
	{
		// This is a confirmation for the object to be created.
		NoeudAbstrait* entityToInsert = nullptr;

		if (!pendingEntityCreationRequests_.empty())
		{
			entityToInsert = pendingEntityCreationRequests_.front();
			pendingEntityCreationRequests_.pop();
			confirmLocalEntity(entityToInsert, entityId);
		}
		else
		{
			createServerEntity(properties, type, entityId, parentId, userId);
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

		if (isOnline_)
		{
			uint32_t entityId = toSelect->getId();
			auto entityIt = confirmedEntities_.find(entityId);
			if (entityIt != confirmedEntities_.end())
			{
				network_->requestEntitySelection(entityId, isSelected);
			}
		} 
		else
		{
			toSelect->setOwnerId(0);
			toSelect->assignerSelection(isSelected);
			toSelect->setSelectionColor({ 1.0, 0.2, 0.0, 1.0 });
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