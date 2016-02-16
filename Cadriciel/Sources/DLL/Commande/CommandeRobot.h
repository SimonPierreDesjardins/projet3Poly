///////////////////////////////////////////////////////////////////////////
/// @file CommandeRobot.h
/// @author Philippe Marcotte
/// @date 2016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef COMMANDE_ROBOT_H
#define COMMANDE_ROBOT_H

#include "NoeudRobot.h"

enum Commande{
	AVANCER,
	RECULER,
	ROTQ,
	ROTDROITE,
	MODEMANUEL,
	MODEAUTO
};

///////////////////////////////////////////////////////////////////////////
/// @class CommandeRobot
/// @brief Classe qui représente une commande qu'on envoie au robot
///		   pour changer ses déplacements ou passer du mode manuel au mode automatique
///
///
/// @author Philippe Marcotte
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class CommandeRobot{
	public:

		/// Constructeur par paramètre permettant de changer la puissance des moteurs du robot
		CommandeRobot(int puissanceMoteurG, int puissanceMoteurD);

		/// Constructeur par paramètre permettant de changer le mode d'utilisation du robot
		CommandeRobot(bool changeAManuel);

		/// Execute les changements associés à la commande sur le robot
		void executer(NoeudRobot* noeud);

	private:
		/// Représente la puissance du moteur de gauche
		int puissanceMoteurG_{ 0 };

		/// Représente la puissance du moteur de droite
		int puissanceMoteurD_{ 0 };

		/// Représente si on change vesr le mode d'utilisation manuel ou non
		bool changeAManuel_{ false };
};

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////