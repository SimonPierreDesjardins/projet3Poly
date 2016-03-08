///////////////////////////////////////////////////////////////////////////////
/// @file ComporterBalayage.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 2016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementBalayage.h"
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assigné
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::ComportementBalayage(ControleRobot* controleRobot) :ComportementAbstrait(controleRobot)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::~ComportementBalayage()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::~ComportementBalayage()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementBalayage::initialiser(){
	// Nous assignons une cible initiale pour la rotation antihoraire de 90 deg
	etatRotation = 0;
	angleCible = controleRobot_->obtenirNoeud()->obtenirAngleRotation() + 90;
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
void ComportementBalayage::mettreAJour(){

	//Si une ligne est trouvée nous passons à la suivie de ligne
	if (controleRobot_->ligneDetectee()){
		controleRobot_->assignerComportement(SUIVIDELIGNE);
	}

	switch (etatRotation){

	// Nous sommes dans la premiere rotation 90 deg antihoraire
	case 0:
		// Envoie la commande de rotation anti-horaire
		controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
		// si tu atteins l'angle voulu
		if (controleRobot_->obtenirNoeud()->obtenirAngleRotation() > angleCible){
			//change l'angle cible et l'état
			angleCible = controleRobot_->obtenirNoeud()->obtenirAngleRotation() - 180;
			etatRotation++;
		}
		break;


	// Nous sommes dans la deuxieme rotation 180 deg horaire
	case 1:
		// Envoie la commande de rotation anti-horaire
		controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
		// si tu atteins l'angle voulu
		if (controleRobot_->obtenirNoeud()->obtenirAngleRotation() < angleCible){
			//change l'angle cible et l'état
			angleCible = controleRobot_->obtenirNoeud()->obtenirAngleRotation() + 90;
			etatRotation++;
		}
		break;

	case 2:
		// Envoie la commande de rotation anti-horaire
		controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
		// si tu atteins l'angle voulu
		if (controleRobot_->obtenirNoeud()->obtenirAngleRotation() > angleCible){
			//TODO: Changer ceci au comportement suivant
			controleRobot_->assignerComportement(DEFAUT);
		}
		break;

	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////