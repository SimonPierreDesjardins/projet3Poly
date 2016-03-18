#include "VisiteurDetectionObstacle.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::VisiteurDetectionObstacle()
///
/// Constructeur par défaut.
///
/// @return Aucune(constructeur). 
///
////////////////////////////////////////////////////////////////////////////////
VisiteurDetectionObstacle::VisiteurDetectionObstacle()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::~VisiteurDetectionObstacle()
///
/// Destructeur.
///
/// @return Aucune(destructeur). 
///
////////////////////////////////////////////////////////////////////////////////
VisiteurDetectionObstacle::~VisiteurDetectionObstacle()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::visiter(ArbreRendu* noeud)
///
/// Méthode permettant d'accèder aux enfants de l'arbre de rendu. 
///
/// @param[in] noeud : le pointeur qui référence l'arbre de rendu.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(ArbreRendu* noeud)
{
	obstacleEstDetecte_ = false;
	noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionLigne::visiter(NoeudTable* noeud)
///
/// Méthode permettant d'accèder aux lignes de la table. 
///
/// @param[in] noeud : le pointeur qui référence la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudTable* noeud)
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionObstacle::visiter(NoeudPoteau* noeud)
///
/// Méthode permettant d'ajuster l'état du capteur en fonction de la distance 
/// du poteau.
///
/// @param[in] noeud : le pointeur qui référence le poteau
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudPoteau* noeud)
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionObstacle::visiter(Noeudmur* noeud)
///
/// Méthode permettant d'ajuster l'état du capteur en fonction de la distance 
/// du mur.
///
/// @param[in] noeud : le pointeur qui référence le mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudMur* noeud)
{
}
