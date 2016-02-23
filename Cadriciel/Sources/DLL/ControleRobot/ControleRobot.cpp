///////////////////////////////////////////////////////////////////////////////
/// @file ControleRobot.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ControleRobot.h"
#include "ComportementDefaut.h"
#include "ComportementSuiviLigne.h"
#include <thread>

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ControleRobot()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::ControleRobot()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::~ControleRobot()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::~ControleRobot()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerComportement(std::shared_ptr<ComportementAbstrait> nouveauComportement)
///
/// Assigne un nouveau comportement à suivre au robot.
///
/// @param nouveauComportement: Le pointeur au comportement assigné.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAuProchainComportement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::passerAModeAutomatique()
///
/// Dit au controleur de robot de gerer la passation au mode automatique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAModeAutomatique(){
	manuel = false;
	comportement = std::make_unique<ComportementDefaut>(ComportementDefaut());
	comportement->initialiser();

	while (!manuel){
		if (ligneDetectee()){
			comportement = std::make_unique<ComportementSuiviLigne>(ComportementSuiviLigne());
			comportement->initialiser();
		}

		comportement->mettreAJour();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::passerAModeManuel()
///
/// Dit au controleur de robot de gerer la passation au mode manuel.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAModeManuel(){
	manuel = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::inverserModeControle()
///
/// Dit au controleur de robot de gerer la passation au mode automatique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::inverserModeControle(){
	if (manuel){
		passerAModeAutomatique();
	}
	else{
		passerAModeManuel();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
///
/// Assigne une nouvelle vitesse aux roues du noeud du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D){
	//TODO: assigner la nouvelle vitesse au noeud du robot
}



////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::passerAModeManuel()
///
/// NON IMPLEMENTEE: Devrait etre migree vers classe des capteurs. Retourne vrai si une ligne est detectee par les capteurs
///
/// @return Si oui ou non une ligne est detectee.
///
////////////////////////////////////////////////////////////////////////
bool ControleRobot::ligneDetectee(){
	return true;

}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
