///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionRobot.h
/// @author Olivier St-Amour
/// @date 2016-02-26
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_ROBOT_H
#define VISITEUR_DETECTION_ROBOT_H

#include "VisiteurAbstrait.h"
#include <array>

class SuiveurLigne;
class CapteurDistance;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant à un capteur optique 
///		   de détecter une ligne à une certaine position. 
///
/// @author Olivier St-Amour
/// @date 2016-02-26
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionRobot : public VisiteurAbstrait
{
public:
	/// Désactiver le constructeur par défaut.
	VisiteurDetectionRobot();
    
    /// Constructeur par paramètres.
    VisiteurDetectionRobot(NoeudRobot* robot);

	/// Destructeur.
	virtual ~VisiteurDetectionRobot();

    /// Visiter l'arbre de rendu.
	virtual void visiter(ArbreRendu* arbre);
    /// Visiter la table.
	virtual void visiter(NoeudTable* table);
    /// Visiter une ligne.
	virtual void visiter(NoeudLigne* ligne);

    /// Visiter un poteau.
    virtual void visiter(NoeudPoteau* noeud);
    /// Visiter un mur.
    virtual void visiter(NoeudMur* noeud);

private:
    NoeudRobot* robot_{ nullptr };
    SuiveurLigne* suiveurLigne_;
    std::array<CapteurDistance, 3>* capteursDistance_;
};

#endif // VISITEUR_DETECTION_LIGNE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////
