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

#include <iostream>

#include "CommandeRobot.h"
#include "NoeudRobot.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

// Inclusion pour l'Enum de comportements
#include "ComportementAbstrait.h"

// TODO: TEMPORAIRE!!! Inclusion pour création des comportements par tests
#include "ComportementDefaut.h"
#include "ComportementSuiviLigne.h"
#include "ComportementBalayage.h"
#include "ComportementDeviation.h"
#include "ComportementEvitement.h"

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
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);
	std::shared_ptr<NoeudAbstrait> robot = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROBOT);
	table_->ajouter(robot);
	robot_ = std::static_pointer_cast<NoeudRobot>(robot).get();
	comportement_ = nullptr;
	passerAModeAutomatique();
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
	//Nous utilisons ceci pour terminer le thread d'IA du robot
	passerAModeManuel();
	NoeudAbstrait* robot = table_->chercher(ArbreRenduINF2990::NOM_ROBOT);
	table_->effacer(robot);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::traiterCommande()
///
/// Demande au controlleur du robot de traiter la commande donnee.
/// Le traitement de la commande dépend du mode du robot. Si le robot est en manuel, les commandes utilisateurs sont traitées.
/// Sinon, les commandes de l'IA sont traitées. La commande d'inversion de mode est toujours traitée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::traiterCommande(CommandeRobot* commande, bool provientUtilisateur)
{
	if (commande != nullptr)
	{
		TypeCommande typeCommande = commande->obtenirTypeCommande();
        
		// Execute la commande que si elle sert à inverser le mode de contrôle.
		if ((typeCommande == INVERSER_MODE_CONTROLE) || (manuel == provientUtilisateur))
		{
			commande->executer(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerComportement(std::shared_ptr<ComportementAbstrait> nouveauComportement)
///
/// Assigne un nouveau comportement à suivre au robot de façon threadsafe et memory safe.
///
/// @param nouveauComportement: Le pointeur au comportement assigné.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerComportement(TypeComportement nouveauComportement)
{
	// Nous devons vérouiller l'accès au comportement temporairement pour sa modification
	mutexComportement.lock();

	//ComportementAbstrait* ancienComportement = comportement_;

	//TODO: ce switch est temporaire, remplacer par recherche de comportement dans profil
	ComportementDeviation* compDev;
	ComportementEvitement* compEvit;
	switch (nouveauComportement){
	case DEFAUT:
		comportement_ = new ComportementDefaut();
		break;
	case BALAYAGE180:
		comportement_ = new ComportementBalayage();
		break;
	case SUIVIDELIGNE:
		comportement_ = new ComportementSuiviLigne();
		break;
	case DEVIATIONVERSLADROITE:
		compDev = new ComportementDeviation();
		compDev->setAngleMaxRotation(-30.0);
		comportement_ = compDev;
		break;
	case DEVIATIONVERSLAGAUCHE:
		compDev = new ComportementDeviation();
		compDev->setAngleMaxRotation(30.0);
		comportement_ = compDev;
		break;
	case EVITEMENTPARLADROITE:
		compEvit = new ComportementEvitement();
		compEvit->setAngleMaxRotation(30.0);
		compEvit->setTempsMaxReculons(2.0);
		comportement_ = compEvit;
		break;
	case EVITEMENTPARLAGAUCHE:
		compEvit = new ComportementEvitement();
		compEvit->setAngleMaxRotation(-30.0);
		compEvit->setTempsMaxReculons(2.0);
		comportement_ = compEvit;
		break;
	}
	
	if (debug){
		std::cout << "Passage au comportement: " << comportement_ -> obtenirNomComportement() << endl;
		//TODO: obtenir le nom du comportement suivant
	}

	// Assignation du controleur au comportement et initialisation
	comportement_->assignerRobot(this);
	comportement_->initialiser();

	// CECI PLANTE POUR UNE RAISON QUELCONQUE, LE MUTEX N'AIDE EN RIEN
	//	if (ancienComportement != nullptr){
	//		delete ancienComportement;
	//	}

	// Libération du mutex, l'accès au comportement redevient valide
	mutexComportement.unlock();
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
/// @fn ControleRobot::passerAModeAutomatique()
///
/// Dit au controleur de robot de gerer la passation au mode automatique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAModeAutomatique() {
	manuel = false;
	//TODO: Ceci doit ammener au comportement par defaut dans profil
	assignerComportement(EVITEMENTPARLAGAUCHE);
	initialiserBoucleRobot();
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
	terminerBoucleRobot();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::initialiserBoucleRobot()
///
/// Initialise le thread de boucle d'éxécution du robot. Appel à l'exécution de boucleInfinieLogiqueRobot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::initialiserBoucleRobot(){
	logiqueRobot = std::make_unique<std::thread>(&ControleRobot::boucleInfinieLogiqueRobot, this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::terminerBoucleRobot()
///
/// Termine le thread de boucle d'éxécution du robot. Aleterne temporairement manuel pour join le thread.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::terminerBoucleRobot(){

	// On garde temporairemtn la valeur de manuel
	bool man = manuel;

	// Le thread roule une fonction tant que manuel = false, alors on change la condition
	manuel = true;

	// Fermeture du thread s'il est joignable
	if ((logiqueRobot != nullptr) && (logiqueRobot->joinable())){
		logiqueRobot->join();
	}

	// Nous redonnons à manuel sa valeur de départ
	manuel = man;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::boucleInfinieLogiqueRobot()
///
/// Appel la mise à jour du comportement tant que manuel est faux. S'exécute normalement dans un thread différent.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::boucleInfinieLogiqueRobot()
{
	while (!manuel) {
		comportement_->mettreAJour();
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
void ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
{
	robot_->assignerVitesseGauche(vit_G);
	robot_->assignerVitesseDroite(vit_D);
}

void ControleRobot::ajouterVitessesMoteurs(double vit_G, double vit_D)
{
    vit_G += robot_->obtenirVitesseGauche();
    vit_D += robot_->obtenirVitesseDroite();
    robot_->assignerVitesseGauche(vit_G);
    robot_->assignerVitesseDroite(vit_D);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::obtenirNoeud()
///
/// Retourne la référence au noeud du robot dans l'arbre de rendu.
///
/// @return Pointeur vers le noeud de noeud de rendu du robot.
///
////////////////////////////////////////////////////////////////////////
NoeudRobot* ControleRobot::obtenirNoeud(){
	return robot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ligneDetectee()
///
/// Fonction indiquant si le robot détecte une ligne. Utilisée par les comportements pour ne pas qu'ils aient
/// à passer par le noeud du robot.
///
/// @return Si oui ou non une ligne est detectee.
///
////////////////////////////////////////////////////////////////////////
bool ControleRobot::ligneDetectee(){
	//TODO: Décommenter pour que le suiveur de ligne fournisse la réponse.
	return 	obtenirNoeud()->obtenirSuiveurLigne() -> obtenirEtatCapteurs() != 0x00;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
