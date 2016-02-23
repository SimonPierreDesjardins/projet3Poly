///////////////////////////////////////////////////////////////////////////////
/// @file Comportement.h
/// @author Olivier St-Amour
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef CONTROLE_ROBOT_H
#define CONTROLE_ROBOT_H

#include "ComportementAbstrait.h"
#include <memory>

///////////////////////////////////////////////////////////////////////////
/// @class ControleRobot
/// @brief Classe qui permet de contrôler le robot. 
///
///        Cette classe permet de contrôler le robot de façon automatique ou 
///		   de façon manuelle em recevant des commandes.
///		   
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ControleRobot
{
public:
	ControleRobot();
	virtual ~ControleRobot();

	void passerAuProchainComportement();


	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	void assignerVitessesMoteurs(double vit_G, double vit_D);

private:
	bool manuel{ false };
	
	std::shared_ptr<ComportementAbstrait> comportement;

	// devrait etre migree vers les capteurs
	bool ligneDetectee();
};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////