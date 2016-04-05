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
	table_ = nullptr;
	robot_ = nullptr;
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	if (arbre != nullptr){
		table_ = arbre->chercher(ArbreRenduINF2990::NOM_TABLE);

		if (table_ != nullptr){
			std::shared_ptr<NoeudAbstrait> robot = arbre->creerNoeud(ArbreRenduINF2990::NOM_ROBOT);

			table_->ajouter(robot);

            robot_ = std::static_pointer_cast<NoeudRobot>(robot).get();
            robot_->assignerMutex(&mutexComportement);
		}
	}


	comportement_ = nullptr;
	vecteurComportements_ = nullptr;

	// init des flags du capteur
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			flagCapteur[i][j] = false;

	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
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
	if (table_ != nullptr && robot_ != nullptr){
		table_->effacer(robot_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::traiterCommande(CommandeRobot* commande, bool provientUtilisateur)
///
/// Demande au controlleur du robot de traiter la commande donnee.
/// Le traitement de la commande dépend du mode du robot. Si le robot est en manuel, les commandes utilisateurs sont traitées et ceux de l'IA ignorées.
/// Sinon, les commandes de l'IA sont traitées et ceux de l'utilisateur ignorées. La commande d'inversion de mode est une exception car elle est toujours traitée.
///
/// @param[in] commande: La commande que doit traiter le robot, soit un changement des vitesses ou une alternance du mode manuel
/// @param[in] provientUtilisateur: Booléen indiquant que la commande provient d'un uitilisateur.
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
			float vitesseG, vitesseD;
			vitesseG = robot_->obtenirVitesseGauche();
			vitesseD = robot_->obtenirVitesseDroite();
			typeSon son;
			if (typeCommande == INVERSER_MODE_CONTROLE)
				son = manuel ? CHANGEMENT_MANUEL_SON : CHANGEMENT_AUTOMATIQUE_SON;
			else if (vitesseG == vitesseD && vitesseG == 0)
				son = ARRETER_SON;
			else if (vitesseG == vitesseD)
				son = AVANCER_RECULER_SON;
			else if (abs(vitesseG) == abs(vitesseD))
				son = TOURNER_SON;
			else
				son = DEVIATION_SON;

			EnginSon::obtenirInstance()->jouerSonRobot(son);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur)
///
/// Assigne un vecteur de comportements au controleur du robot auquel il se réfèrera lors de son éxécution.
///
/// @param[in] vecteur: Le pointeur au vecteur de comportements que le controlleur devra utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur){
	vecteurComportements_ = vecteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerComportement(TypeComportement nouveauComportement, std::string declencheur)
///
/// Assigne un nouveau comportement à suivre au robot de façon threadsafe et memory safe.
///
/// @param nouveauComportement: Le pointeur au comportement assigné.
/// @param declencheur: Indique la raison du changement de comportement. Utilisé pour le deboguage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerComportement(TypeComportement nouveauComportement, std::wstring declencheur)
{
	// Nous devons vérouiller l'accès au comportement temporairement pour sa modification
	mutexComportement.lock();

	//ComportementAbstrait* ancienComportement = comportement_;
	comportement_ = vecteurComportements_ -> at(nouveauComportement).get();
	
	if ((profil_ != nullptr) && profil_->obtenirOptionDebogage(DEBOGAGE_COMPORTEMENTS)){
		utilitaire::time_in_HH_MM_SS_MMM();
		std::wcout << L" - " << declencheur << L" - " << comportement_->obtenirNomComportement() << endl;
	}

	// Assignation du controleur au comportement et initialisation
	comportement_->assignerRobot(this);
	comportement_->initialiser();

	// Libération du mutex, l'accès au comportement redevient valide
	mutexComportement.unlock();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::inverserModeControle()
///
/// Dit au controleur de robot d'inverser le type de commande
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
	assignerComportement(DEFAUT, L"Passage au mode automatique");
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
		logiqueRobot = nullptr;
	}

	// Nous redonnons à manuel sa valeur de départ
	manuel = man;
	
	traiterCommande(&CommandeRobot(ARRETER), false);
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
	while (!manuel) 
	{
		if (!enPause){
			if (robot_ != nullptr){
				verifierCapteurs();
			}
			comportement_->mettreAJour();
		}
		else{
			traiterCommande(&CommandeRobot(ARRETER), false);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::verifierCapteurs()
///
/// Vérifie l'état des capteurs à obstacles et change de comportement au besoin.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::verifierCapteurs(){
	NoeudRobot::ConteneurCapteursDistance* capteurs = robot_->obtenirCapteursDistance();
	std::wstring declencheur;
	for (int i = 0; i < capteurs->size(); i++)
	{
		declencheur = L"Obstacle capté à ";
		switch (i)
		{
		case 0:
			declencheur += L"droite: ";
			break;
		case 1:
			declencheur += L"centre: ";
			break;
		case 2:
			declencheur += L"gauche: ";
			break;
		}
		// Si le robot est en plein mise à jour, attendre qu'il ait terminé sa mise à jour.
        mutexComportement.lock();
        EtatCapteurDistance etat = capteurs->at(i).obtenirEtat();
        mutexComportement.unlock();

		if (etat == DETECTION_ZONE_SECURITAIRE )
		{
			if (!flagCapteur[i][0]){
				// On empêche plusieurs detections à la fois
				flagCapteur[i][0] = true;
				declencheur += L"Zone securitaire";
				assignerComportement(capteurs->at(i).obtenirComportementZoneSecuritaire(), declencheur);
			}
			else{
				//cout << "Input ignored" << endl;
			}
		}
		else{
			//On permet la detection
			//std::cout << "Flag " << i << " securitaire disabled" << endl;
			flagCapteur[i][0] = false;
		}

		// vérifions la zone dangereuse
		if (etat == DETECTION_ZONE_DANGER)
		{
			if (!flagCapteur[i][1]){
				// On empêche plusieurs detections à la fois
				flagCapteur[i][1] = true;
				declencheur += L"Zone dangereuse";
				assignerComportement(capteurs->at(i).obtenirComportementZoneDanger(), declencheur);
			}
			else{
				//cout << "Input ignored" << endl;
			}
		}
		else{
			// On permet la detection
            //std::cout << "Flag " << i << " dangereuse disabled" << endl;
			flagCapteur[i][1] = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
///
/// Assigne une nouvelle vitesse aux roues du noeud du robot
///
/// @param vit_G: La vitesse à la roue gauche
/// @param vit_D: La vitesse à la roue droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
{
	if (robot_ != nullptr){
		robot_->assignerVitesseGauche(vit_G);
		robot_->assignerVitesseDroite(vit_D);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
///
/// Assigne une nouvelle vitesse aux roues du noeud du robot
///
/// @param vit_G: La vitesse à la roue gauche
/// @param vit_D: La vitesse à la roue droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::ajouterVitessesMoteurs(double vit_G, double vit_D)
{
	if (robot_ != nullptr){
		vit_G += robot_->obtenirVitesseGauche();
		vit_D += robot_->obtenirVitesseDroite();
		robot_->assignerVitesseGauche(vit_G);
		robot_->assignerVitesseDroite(vit_D);
	}
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
	bool ret = false;
	if ((robot_ != nullptr) && (robot_->obtenirSuiveurLigne() != nullptr)){
		ret = robot_->obtenirSuiveurLigne()->obtenirEtatCapteurs() != 0x00;
	}
	return 	ret;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::setEnPause(bool pause)
///
/// Fonction permettant d'assigner une valeur au booléen enPause;
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::setEnPause(bool pause)
{
	enPause = pause;
}


bool ControleRobot::getEnPause()
{
	return enPause;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
