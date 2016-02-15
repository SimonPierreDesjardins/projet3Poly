///////////////////////////////////////////////////////////////////////////
/// @file VisiteurCreationLigne.cpp
/// @author Frederic Gregoire
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurCreationLigne.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationLigne::VisiteurCreationLigne()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationLigne::VisiteurCreationLigne()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationLigne::~VisiteurCreationLigne()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurCreationLigne::~VisiteurCreationLigne()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationLigne::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationLigne::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCreationLigne::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud Ligne au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter la ligne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCreationLigne::visiter(NoeudTable* noeud)
{
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);
	nouveauNoeud->assignerPositionRelative(positionRelative_);
	noeud->ajouter(nouveauNoeud);
	referenceNoeud_ = nouveauNoeud.get();
}