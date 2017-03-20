///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include <iostream>

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include "MapSession.h"

#include "VisiteurSuppression.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression(client_network::MapSession * mapSession)
	: mapSession_(mapSession)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::~VisiteurSuppression()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression()
{
}

void VisiteurSuppression::visiter(ArbreRendu* tree)
{
	tree->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::visiter(NoeudTable* noeud)
///
/// Fonction qui efface tous les enfants de la table passée en paramètre qui sont sélectionnés .
///
/// @param[in] noeud : noued Table de laquelle on veut supprimer les enfants sélectionnés.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudTable* table)
{
	uint32_t nChildren = table->obtenirNombreEnfants();
	for (int i = 0; i < nChildren; ++i)
	{
		NoeudAbstrait* child = table->chercher(i);
		if (child->estSelectionne() && child->getOwnerId() == mapSession_->getThisUserId())
		{
			deleteSelectedEntityAndChildren(child);
		}
	}
}

void VisiteurSuppression::visiter(NoeudDuplication * duplication)
{
	deleteSelectedEntityAndChildren(duplication);
}

void VisiteurSuppression::deleteSelectedEntityAndChildren(NoeudAbstrait* entity)
{
	// When a node is deleted, indexes of the chilren are invalidated.
	// We don't want to search again from the beginning (O(n^2)) so we use a 2 pass algorithm (O(n)).
	std::vector<NoeudAbstrait*> toDeleteList;
	
	// First pass to list the nodes to delete.
	uint32_t nChildren = entity->obtenirNombreEnfants();
	for (int i = 0; i < nChildren; ++i)
	{
		NoeudAbstrait* child = entity->chercher(i);
		if (child->estSelectionne() && child->getOwnerId() == mapSession_->getThisUserId())
		{
			toDeleteList.push_back(child);
		}
	}

	// Second pass to delete the listed nodes.
	for (int i = 0; i < toDeleteList.size(); ++i)
	{
		mapSession_->deleteLocalEntity(toDeleteList[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////