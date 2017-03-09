///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

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
	NoeudAbstrait* enfant;
	glm::dvec3 positionVirtuelle;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne()) {
			positionVirtuelle = enfant->obtenirPositionRelative();
			enfant->assignerPositionRelative(positionVirtuelle + positionRelative_);
			enfant->assignerPositionCourante(positionVirtuelle + positionRelative_);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////