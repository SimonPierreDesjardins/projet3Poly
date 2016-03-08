///////////////////////////////////////////////////////////////////////////////
/// @file ComporterSuiviLigne.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementSuiviLigne.h"
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::ComportementSuiviLigne()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementSuiviLigne::ComportementSuiviLigne()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::~ComportementSuiviLigne()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementSuiviLigne::~ComportementSuiviLigne()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementSuiviLigne::initialiser(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::mettreAJour()
///
/// Vérifie si le comportement doit changer ou procéder à une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementSuiviLigne::mettreAJour(){
	uint8_t etatSuiveurLigne = controleRobot_->obtenirNoeud()->obtenirSuiveurLigne()->obtenirEtatCapteurs();

	// Tant que nous n'avons pas perdu la ligne, on la suit
	if (!rechercheLigne){

		switch (etatSuiveurLigne){
		case (0x07) :
		case(0x04) :
			controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
			break;
		case(0x06) :
			controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_GAUCHE), false);
			break;
		case(0x01) :
			controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
			break;
		case(0x03) :
			controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_DROITE), false);
			break;
		case(0x02) :
			controleRobot_->traiterCommande(&CommandeRobot(AVANCER), false);
			break;
		default:
			// On a perdu la ligne
			rechercheLigne = true;
			heurePerteLigne_ = time(nullptr);
			break;
		}
	}
	// Si nous avons perdu la ligne, on se laisse une chance
	else{
		// ligne retrouvée!
		if (etatSuiveurLigne != 0x00){
			rechercheLigne = false;
		}
		// trop tard, change de comportement
		else if (difftime(time(nullptr), heurePerteLigne_) > 1.0){
			// TODO: obtenir le comportement du profil
			controleRobot_->assignerComportement(DEFAUT);
		}

	}
	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
