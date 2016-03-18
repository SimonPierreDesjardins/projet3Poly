///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionObstacle.h
/// @author Olivier St-Amour
/// @date 2016-02-28
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_OBSTACLE_H
#define VISITEUR_DETECTION_OBSTACLE_H

#include "VisiteurAbstrait.h"
#include "CapteurDistance.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant à un capteur de distance de détecter un 
///        mur ou un poteau.
///
/// @author Olivier St-Amour
/// @date 2016-02-28
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionObstacle : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDetectionObstacle();
	/// Destructeur.
	virtual ~VisiteurDetectionObstacle();

    /// Assigner une référence à un capteur optique.
	inline void assignerCapteurDistance(CapteurDistance* capteur);

    /// Visiter l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
    /// Visiter la table.
	virtual void visiter(NoeudTable* noeud);
    /// Visiter un poteau.
	virtual void visiter(NoeudPoteau* noeud);
    /// Visiter un mur.
	virtual void visiter(NoeudMur* noeud);

private:
    CapteurDistance* capteur_;
    
	bool obstacleEstDetecte_{ false };
	glm::dvec3 positionCapteur_;
};

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::assignerCapteurDistance(CapteurDistance* capteur)
///
/// Cette méthode assigne une référence au capteur.
///
/// @param[in] capteur : le pointeur qui référence le capteur.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
inline void VisiteurDetectionObstacle::assignerCapteurDistance(CapteurDistance* capteur)
{
}

#endif // VISITEUR_DETECTION_OBSTACLE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

