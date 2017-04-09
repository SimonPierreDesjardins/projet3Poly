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
class ProfilUtilisateur;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant � un capteur optique 
///		   de d�tecter une ligne � une certaine position. 
///
/// @author Olivier St-Amour
/// @date 2016-02-26
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionRobot : public VisiteurAbstrait
{
public:
	/// D�sactiver le constructeur par d�faut.
	VisiteurDetectionRobot();
    
    /// Constructeur par param�tres.
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

	virtual void visiter(NoeudTeleporteur* noeud);

	virtual void visiter(NoeudPiece* noeud);

	virtual void visiter(NoeudRobot* robot);

	virtual void visiter(NoeudLigneCourseAbstrait* checkpoint);

	virtual void visiter(NoeudPaireTeleporteurs* noeud);

	bool collisionTeleporteur(NoeudTeleporteur* teleporteur);


private:
    NoeudRobot* robot_{ nullptr };
    SuiveurLigne* suiveurLigne_;
    std::array<CapteurDistance, 3>* capteursDistance_;
	bool estEnCollision_{ false };
};

#endif // VISITEUR_DETECTION_LIGNE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////
