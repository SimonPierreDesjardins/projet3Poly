///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationTeleporteur.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "Vue.h"
#include "VisiteurCreationTeleporteur.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationTeleporteur::VisiteurCreationTeleporteur()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationTeleporteur::VisiteurCreationTeleporteur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationTeleporteur::~VisiteurCreationTeleporteur()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationTeleporteur::~VisiteurCreationTeleporteur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationTeleporteur::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationTeleporteur::visiter(ArbreRendu* noeud)
{
	arbre_ = noeud;
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationTeleporteur::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud teleporteur au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter le teleporteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationTeleporteur::visiter(NoeudTable* noeud)
{
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre_->creerNoeud(ArbreRenduINF2990::NOM_TELEPORTEUR);
	PhysicsComponent& physics = nouveauNoeud->getPhysicsComponent();
	physics.relativePosition = positionRelative_;
	physics.absolutePosition = positionRelative_;
	referenceNoeud_ = nouveauNoeud;
}

std::shared_ptr<NoeudAbstrait> VisiteurCreationTeleporteur::obtenirReferenceNoeud()
{
	return referenceNoeud_;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////