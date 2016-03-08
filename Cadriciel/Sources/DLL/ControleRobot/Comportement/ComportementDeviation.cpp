///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementDeviation.h"
#include "ControleRobot.h"
#include "CommandeRobot.h"
#include "NoeudRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation()
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assigné
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(ControleRobot* controleRobot) :ComportementAbstrait(controleRobot)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::~ComportementDeviation()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::~ComportementDeviation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::initialiser(){
	angleCible_ = controleRobot_->obtenirNoeud()->obtenirAngleRotation() + maxAngle_;
	gauche = maxAngle_ >= 0;
	ignorerLigne_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::mettreAJour()
///
/// Vérifie si le comportement doit changer ou procéder à une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::mettreAJour(){
	//TODO: Implémenter l'exception
	//Implémentation de l'exception Rapport d'élicitation p.22
	if (controleRobot_->ligneDetectee()){
		if (!ignorerLigne_){
			controleRobot_->assignerComportement(SUIVIDELIGNE);
		}
	}
	else{
		ignorerLigne_ = false;
	}

	bool angleAtteinte = false;

	// Rotation du robot
	if (gauche){
		// Dévier à gauche et vérifier angle
		controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_GAUCHE), false);
		angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() > angleCible_;
	}
	else{
		// Dévier à droite et vérifier angle
		controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_DROITE), false);
		angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() < angleCible_;
	}

	if (angleAtteinte){
		// TODO: Assigner le comportement suivant
		controleRobot_->assignerComportement(DEFAUT);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::setAngleMaxRotation(double angle)
///
/// Ajuste l'angle pour la déviation
///
/// @param[in] angle: l'angle à partir duquel on change decomportement. negatif implique une deviation vers la droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::setAngleMaxRotation(double angle){
	maxAngle_ = angle;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
