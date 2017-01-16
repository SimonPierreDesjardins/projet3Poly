///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationMur.cpp
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationMur.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationMur::VisiteurCreationMur()
///
/// Constructeur
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationMur::VisiteurCreationMur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationMur::~VisiteurCreationMur()
///
/// Destructeur
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationMur::~VisiteurCreationMur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationMur::visiter(AbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationMur::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationLigne::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud Mur au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter le mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationMur::visiter(NoeudTable* noeud)
{
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_MUR);
	referenceNoeud_ = nouveauNoeud.get();
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////