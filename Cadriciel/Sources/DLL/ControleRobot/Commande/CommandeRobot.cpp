///////////////////////////////////////////////////////////////////////////
/// @file CommandeRobot.cpp
/// @author Philippe Marcotte
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "CommandeRobot.h"

///////////////////////////////////////////////////////////////////////////
/// @fn Commande::CommandeRobot(Commande commande)
/// @brief Constructeur par paramètre d'une CommandeRobot.
///		   Elle définie la puissance des moteurs selon le type de commande.
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
CommandeRobot::CommandeRobot(TypeCommande commande){
	typeCommande_ = commande;
	switch (commande)
	{
	case AVANCER:
		vitesseMoteurD_ = 100.0;
		vitesseMoteurG_ = 100.0;
		break;
	
	case RECULER:
		vitesseMoteurD_ = -100.0;
		vitesseMoteurG_ = -100.0;
		break;
	
	case ROTATION_GAUCHE:
		vitesseMoteurD_ = 100.0;
		vitesseMoteurG_ = -100.0;
		break;
	
	case ROTATION_DROITE:
		vitesseMoteurD_ = -100.0;
		vitesseMoteurG_ = 100.0;
		break;

	case DEVIATION_GAUCHE:
		vitesseMoteurD_ = 100.0;
		vitesseMoteurG_ = 50.0;
		break;

	case DEVIATION_DROITE:
		vitesseMoteurD_ = 50.0;
		vitesseMoteurG_ = 100.0;
		break;
	
	case ARRETER:
		vitesseMoteurD_ = 0.0;
		vitesseMoteurG_ = 0.0;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////
/// @fn void CommandeRobot::executer(NoeudRobot* noeud)
/// @brief Fonction exécutant la commande en modifiant les attributs du robot.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
void CommandeRobot::executer(ControleRobot* ia){
	if (typeCommande_ == INVERSER_MODE_CONTROLE)
		ia->inverserModeControle();
	ia->assignerVitessesMoteurs( vitesseMoteurG_, vitesseMoteurD_);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////