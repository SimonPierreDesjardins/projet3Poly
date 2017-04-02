///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include <queue>

#include "MapSession.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

#include "VisiteurDeplacement.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement(client_network::MapSession * mapSession)
	: mapSession_(mapSession)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::~VisiteurDeplacement()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::visiter(NoeudTable* noeud)
///
/// Fonction qui applique un déplacement aux noeuds enfants de la table passée en paramètre qui sont sélectionnés.
///
/// @param[in] noeud : Le noeud Table contenant les noeuds auxquels on veut appliquer le déplacement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudTable* table)
{
	moveSelectedChildren(table);
}

void VisiteurDeplacement::visiter(NoeudDuplication* duplication)
{
	PhysicsComponent& physics = duplication->getPhysicsComponent();
	physics.relativePosition += positionRelative_;
	physics.absolutePosition = duplication->obtenirParent()->getPhysicsComponent().absolutePosition + physics.relativePosition;

	mapSession_->localEntityPropertyUpdated(duplication, Networking::ABSOLUTE_POSITION, glm::vec3(physics.absolutePosition));
	mapSession_->localEntityPropertyUpdated(duplication, Networking::RELATIVE_POSITION, glm::vec3(physics.relativePosition));

	// Update the relative position of all the children and push them in the queue.
	std::queue<NoeudAbstrait*> entitiesToMove;
	uint32_t nChildren = duplication->obtenirNombreEnfants();
	
	for (uint32_t i = 0; i < nChildren; ++i) 
	{
		// All the child will be selected and me move them all.
		entitiesToMove.push(duplication->chercher(i));
	}

	// Non-recursive top down update of the absolute position. 
	while (!entitiesToMove.empty())
	{
		// Get the entity in front of the queue.
		NoeudAbstrait* entityToUpdate = entitiesToMove.front();
		entitiesToMove.pop();

		NoeudAbstrait* parent = entityToUpdate->obtenirParent();

		// Update the absolute position (absolute from parent + child relative position)
		PhysicsComponent& physics = entityToUpdate->getPhysicsComponent();
		physics.absolutePosition = physics.relativePosition + parent->getPhysicsComponent().absolutePosition;

		mapSession_->localEntityPropertyUpdated(entityToUpdate, Networking::ABSOLUTE_POSITION, 
												glm::vec3(physics.absolutePosition));

		// Push the children in the queue.
		uint32_t nChildren = entityToUpdate->obtenirNombreEnfants();
		for (int i = 0; i < nChildren; ++i)
		{
			entitiesToMove.push(entityToUpdate->chercher(i));
		}
	}
}

void VisiteurDeplacement::moveSelectedChildren(NoeudAbstrait* entity)
{
	// Update the relative position of all the children and push them in the queue.
	std::queue<NoeudAbstrait*> entitiesToMove;
	for (unsigned int i = 0; i < entity->obtenirNombreEnfants(); i++) {
		NoeudAbstrait* child = entity->chercher(i);

		// If the node is selected and the owner is me.
		if (child->estSelectionne() && child->getOwnerId() == mapSession_->getThisUserId()) 
		{
			entitiesToMove.push(child);
			PhysicsComponent& physics = child->getPhysicsComponent();
			physics.relativePosition += positionRelative_;
			mapSession_->localEntityPropertyUpdated(child, Networking::RELATIVE_POSITION, glm::vec3(physics.relativePosition));
		}
	}

	// Non-recursive top down update of the absolute position. 
	while (!entitiesToMove.empty())
	{
		// Get the entity in front of the queue.
		NoeudAbstrait* entityToUpdate = entitiesToMove.front();
		entitiesToMove.pop();

		NoeudAbstrait* parent = entityToUpdate->obtenirParent();

		PhysicsComponent& physics = entityToUpdate->getPhysicsComponent();
		physics.absolutePosition = physics.relativePosition + parent->getPhysicsComponent().absolutePosition;
		mapSession_->localEntityPropertyUpdated(entityToUpdate, Networking::ABSOLUTE_POSITION, 
												glm::vec3(physics.absolutePosition));

		// Push the children in the queue.
		uint32_t nChildren = entityToUpdate->obtenirNombreEnfants();
		for (int i = 0; i < nChildren; ++i)
		{
			entitiesToMove.push(entityToUpdate->chercher(i));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////