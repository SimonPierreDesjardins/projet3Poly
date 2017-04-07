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

#include <cmath>
////////////////////////////////////////////////////////////////////////////////
///
/// @fn CommandeRobot::CommandeRobot()
///
/// Constructeur par d�faut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CommandeRobot::CommandeRobot()
{
}


///////////////////////////////////////////////////////////////////////////
/// @fn Commande::CommandeRobot(Commande commande)
/// @brief Constructeur par param�tre d'une CommandeRobot.
///		   Elle d�finie la puissance des moteurs selon le type de commande.
///
/// @return Aucune (constructeur).
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
CommandeRobot::CommandeRobot(TypeCommande commande){
	EnginSon::obtenirInstance();
	typeCommande_ = commande;
	switch (commande)
	{
	case AVANCER:
		puissanceMoteurD_ = MAX_POWER;
		puissanceMoteurG_ = MAX_POWER;
		break;
	
	case RECULER:
		puissanceMoteurD_ = -MAX_POWER;
		puissanceMoteurG_ = -MAX_POWER;
		break;
	
	case ROTATION_GAUCHE:
		puissanceMoteurD_ = MAX_POWER;
		puissanceMoteurG_ = -MAX_POWER;
		break;
	
	case ROTATION_DROITE:
		puissanceMoteurD_ = -MAX_POWER;
		puissanceMoteurG_ = MAX_POWER;
		break;

	case DEVIATION_GAUCHE:
		puissanceMoteurD_ = MAX_POWER;
		puissanceMoteurG_ = LOW_POWER;
		break;

	case DEVIATION_DROITE:
		puissanceMoteurD_ = LOW_POWER;
		puissanceMoteurG_ = MAX_POWER;
		break;
	
	case ARRETER:
		puissanceMoteurD_ = 0.0;
		puissanceMoteurG_ = 0.0;
	default:
		break;
	}
}


///////////////////////////////////////////////////////////////////////////
/// @fn Commande::CommandeRobot(Commande type, const bool& ajout)
/// @brief Constructeur par param�tre d'une CommandeRobot.
///
///		   Elle d�finie la puissance des moteurs selon le type de commande et 
///        indique si la commande remplace ou s'ajoute � la vitesse  du robot. 
///
/// @param[in] type : Le type de commande.
/// @param[in] ajout : Indique si la commande est un ajout.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
CommandeRobot::CommandeRobot(TypeCommande type, const bool& ajout)
    : CommandeRobot(type)
{
    ajout_ = ajout;
}


///////////////////////////////////////////////////////////////////////////
/// @fn void CommandeRobot::inverserVitesseMoteurs()
/// @brief M�thode permettant d'inverser la vitesse des moteurs.
///
///        Cette m�thode sert � inverser l'�tat d'une commande dans le but 
///        de r�tablir l'�tat ant�rieur du robot.
///
/// @return Aucune (constructeur).
///
///////////////////////////////////////////////////////////////////////////
void CommandeRobot::inverserVitesseMoteurs()
{
    puissanceMoteurD_ = -puissanceMoteurD_;
    puissanceMoteurG_ = -puissanceMoteurG_;
}


///////////////////////////////////////////////////////////////////////////
/// @fn void CommandeRobot::executer(NoeudRobot* noeud)
/// @brief Fonction ex�cutant la commande en modifiant les attributs du robot.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
void CommandeRobot::executer(ControleRobot* ia){
	if (ajout_){
		ia->ajouterVitessesMoteurs(puissanceMoteurG_, puissanceMoteurD_);
	}
    else 
	    ia->assignerVitessesMoteurs(puissanceMoteurG_, puissanceMoteurD_);

	if (typeCommande_ == INVERSER_MODE_CONTROLE)
		ia->inverserModeControle();
	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
