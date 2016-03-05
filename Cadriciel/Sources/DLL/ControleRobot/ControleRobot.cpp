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

#include "CommandeRobot.h"
#include "NoeudRobot.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

// Inclusion pour l'Enum de comportements
#include "ComportementAbstrait.h"

// TEMPORAIRE!!! Inclusion pour création du comportement par defaut
#include "ComportementDefaut.h"
#include "ComportementSuiviLigne.h"
#include "ComportementBalayage.h"

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
void ControleRobot::assignerComportement(eComportement nouveauComportement)
{
	// Nous devons vérouiller l'accès au comportement temporairement pour sa modification
	mutexComportement.lock();

	//ComportementAbstrait* ancienComportement = comportement_;

	//TODO: ce switch est temporaire, remplacer par recherche de comportement dans profil
	switch (nouveauComportement){
	case DEFAUT:
		comportement_ = new ComportementDefaut(this);
		break;
	case BALAYAGE180:
		comportement_ = new ComportementBalayage(this);
		break;
	}
	

	// Initialisation du comportement
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
	assignerComportement(BALAYAGE180);
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
void ControleRobot::boucleInfinieLogiqueRobot(){
	while (!manuel) {
		/*if (ligneDetectee()){
		comportement = std::make_unique<ComportementSuiviLigne>(ComportementSuiviLigne());
		comportement->initialiser();
		}*/
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
