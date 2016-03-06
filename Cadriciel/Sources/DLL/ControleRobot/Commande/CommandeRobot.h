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

#include "ControleRobot.h"

enum TypeCommande
{
	INVERSER_MODE_CONTROLE,
	AVANCER,
	RECULER,
	ROTATION_GAUCHE,
	ROTATION_DROITE,
	DEVIATION_GAUCHE,
	DEVIATION_DROITE,
	ARRETER
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
		CommandeRobot(TypeCommande commande);

		/// Execute les changements associés à la commande sur le robot
		void executer(ControleRobot* ia);

		void assignerVitessesMoteurs(double vit_g, double vit_d);

		inline TypeCommande obtenirTypeCommande();

		inline bool provientUtilisateur();

	private:
		/// Représente la nouvelle vitesse du moteur de gauche
		double vitesseMoteurG_{ 0 };

		/// Représente la nouvelle vitesse du moteur de droite
		double vitesseMoteurD_{ 0 };

		/// Représente si l'on change le mode d'utilisation du robot ou non. Si oui, celle-ci correspondra à un des deux modes d'utilisation (MODE_MANUEL ou MODE_AUTO)
		TypeCommande typeCommande_;
};


///////////////////////////////////////////////////////////////////////////
/// @fn CommandeRobot::obtenirTypeCommande()
/// @brief Fonction permettant d'obtenir la nature de la commande.
///
/// @return Retourne le type de commande associé.
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
inline TypeCommande CommandeRobot::obtenirTypeCommande()
{
	return typeCommande_;
}

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////