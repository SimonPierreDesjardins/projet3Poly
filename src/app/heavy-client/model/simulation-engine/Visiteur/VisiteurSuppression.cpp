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
	std::vector<NoeudAbstrait*> toDeleteList;

	uint32_t nChildren = table->obtenirNombreEnfants();
	for (uint32_t i = 0; i < nChildren; ++i)
	{
		NoeudAbstrait* child = table->chercher(i);
		if (child->estSelectionne() && child->isErasable() &&
			child->getOwnerId() == mapSession_->getThisUserId())
		{
			toDeleteList.push_back(child);
		}
	}

	for (int i = 0; i < toDeleteList.size(); ++i)
	{
		mapSession_->deleteLocalEntity(toDeleteList[i]);
	}
}

void VisiteurSuppression::visiter(NoeudDuplication* duplication)
{
	mapSession_->deleteLocalEntity(duplication);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////