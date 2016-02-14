///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationPoteau.cpp
/// @author Olivier St-Amour
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationPoteau.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationPoteau::VisiteurCreationPoteau()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationPoteau::VisiteurCreationPoteau()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationPoteau::~VisiteurCreationPoteau()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationPoteau::~VisiteurCreationPoteau()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationPoteau::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationPoteau::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationPoteau::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud Poteau au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter le poteau.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationPoteau::visiter(NoeudTable* noeud)
{
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
}