///////////////////////////////////////////////////////////////////////////
/// @file CapteurDistance.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class CapteurDistance
/// @brief Classe qui représente un capteur de distance du robot.  
///
///        Cette classe s'occupe de gérer la détection des poteaux et des murs. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class CapteurDistance
{
public:
	//Constructeur par défaut
	CapteurDistance();
	//Destructeur
	~CapteurDistance();

	void assignerActif(bool estActif);

	void assignerParametreZoneDanger(TypeComportement comportement, double distance);

	void assignerParametreZoneSecuritaire(TypeComportement comportement, double distance);

private:
	bool estActif_{ true };
};

#endif // CAPTEUR_DISTANCE_H