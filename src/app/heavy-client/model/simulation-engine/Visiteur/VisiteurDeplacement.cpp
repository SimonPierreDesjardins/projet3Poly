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
VisiteurDeplacement::VisiteurDeplacement()
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

void VisiteurDeplacement::shiftSelectedEntities(ArbreRendu* tree, client_network::MapSession* mapSession)
{
	mapSession_ = mapSession;
	tree->accepterVisiteur(this);
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
void VisiteurDeplacement::visiter(NoeudTable* noeud)
{
	std::queue<NoeudAbstrait*> entitiesToMove;

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		NoeudAbstrait* enfant = noeud->chercher(i);

		// If the node is selected and the owner is me.
		if (enfant->estSelectionne() && enfant->getOwnerId() == mapSession_->getThisUserId()) 
		{
			entitiesToMove.push(enfant);
			glm::dvec3 positionRelative = enfant->obtenirPositionRelative();
			positionRelative += positionRelative_;
			enfant->assignerPositionRelative(positionRelative);
			if (mapSession_)
			{
				mapSession_->localEntityPropertyUpdated(enfant, Networking::RELATIVE_POSITION, glm::vec3(positionRelative));
			}
		}
	}

	// Update absolute position of the entities.
	while (!entitiesToMove.empty())
	{
		NoeudAbstrait* entityToUpdate = entitiesToMove.front();
		entitiesToMove.pop();
		NoeudAbstrait* parent = entityToUpdate->obtenirParent();

		glm::dvec3 updatedAbsolutePosition = entityToUpdate->obtenirPositionRelative() +
											 parent->obtenirPositionCourante();

		entityToUpdate->assignerPositionCourante(updatedAbsolutePosition);
		if (mapSession_)
		{
			mapSession_->localEntityPropertyUpdated(entityToUpdate, Networking::ABSOLUTE_POSITION, 
													glm::vec3(updatedAbsolutePosition));
		}

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