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

enum Commande
{
	MODE_MANUEL,
	MODE_AUTO,
	AVANCER,
	RECULER,
	ROTATION_GAUCHE,
	ROTATION_DROITE
};

///////////////////////////////////////////////////////////////////////////
/// @class CommandeRobot
/// @brief Classe qui représente une commande qu'on envoie au robot
///		   pour changer ses déplacements ou passer du mode manuel au mode automatique.
///		   Celle-ci fonctionne selon les principes du patron Visiteur.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class CommandeRobot{
	public:
		/// Constructeur par paramètre permettant de changer la puissance des moteurs du robot ou de changer le mode d'utilisation de celui-ci
		CommandeRobot(Commande commande);

		/// Execute les changements associés à la commande sur le robot
		void executer(NoeudRobot* noeud);

	private:
		/// Représente la nouvelle puissance du moteur de gauche
		int puissanceMoteurG_{ 0 };

		/// Représente la nouvelle puissance du moteur de droite
		int puissanceMoteurD_{ 0 };

		/// Représente si l'on change le mode d'utilisation du robot ou non. Si oui, celle-ci correspondra à un des deux modes d'utilisation (MODE_MANUEL ou MODE_AUTO)
		Commande typeCommande_;
};

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////