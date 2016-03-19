///////////////////////////////////////////////////////////////////////////////
/// @file Comportement.h
/// @author Olivier St-Amour
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef CONTROLE_ROBOT_H
#define CONTROLE_ROBOT_H

#include <memory>
#include <thread>
#include "ComportementAbstrait.h"
#include <mutex>
#include <vector>

class CommandeRobot;
class NoeudAbstrait;
class NoeudRobot;
class ArbreRendu;
class ProfilUtilisateur;

///////////////////////////////////////////////////////////////////////////
/// @class ControleRobot
/// @brief Classe qui permet de contrôler le robot. 
///
///        Cette classe permet de contrôler le robot de façon automatique ou 
///		   de façon manuelle em recevant des commandes.
///		   
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ControleRobot
{
	friend class ModeSimulation;
	friend class ModeTest;
public:
	ControleRobot();
	~ControleRobot();

	// Demande au robot de traiter une commande donnée
	void traiterCommande(CommandeRobot* commande, bool provientUtilisateur);

	// Assigne le comportement correspondant à l'enum à l'IA du robot.
	void assignerComportement(TypeComportement nouveauComportement, std::string declencheur);

	// perme d'obtenir le noeud du robot. Souvent appelé par les comportements pour vérifier des conditions.
	NoeudRobot* obtenirNoeud();

	// Fonctions permettant d'alterner entre les modes de contrôle
	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	// Peut-être rendre ceci privé, l'ajustement de moteurs devrait se faire par commandes
	void assignerVitessesMoteurs(double vit_G, double vit_D);
    void ajouterVitessesMoteurs(double vit_G, double vit_D);

	// Permet aux comportements de savoir si une ligne est détectée
	bool ligneDetectee();

	void assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur);

	void setEnPause(bool pause);
	bool getEnPause();

private:
	// Fonctions pour gérer multithreading robot
	void initialiserBoucleRobot();
	void terminerBoucleRobot();
	void boucleInfinieLogiqueRobot();

	// Fonction qui verifie et effectue les changements en fonction des capteurs à obstacles
	void verifierCapteurs();

	// définit si oui ou non le robot est en mode manuel
	bool manuel{ false };

	// définit si en mode debug
	bool enPause{ false };

	ArbreRendu* arbre_;
	NoeudAbstrait* table_;

	// pointeur vers le noeud du robot
	NoeudRobot* robot_;
	//Pointeur sur un profil
	ProfilUtilisateur* profil_{ nullptr };

	std::vector<std::unique_ptr<ComportementAbstrait>>* vecteurComportements_;

	// Pointeur vers le comportement présentement adopté par le robot.
	ComportementAbstrait* comportement_;

	//Mutex servant à traiter l'accès au comportement du robot.
	std::mutex mutexComportement;

	// Pointeur vers le thread d'exécution du robot
	std::unique_ptr<std::thread> logiqueRobot;

	/*
	* Représente les flags des capteurs, évite de capter plusieurs fois dans le debugger
	* flagCapteur[X][Y]
	* X: 0 = droite, 1 = centre, 2 = gauche
	* Y: 0 = zone securitaire, 1 = zone danger */
	bool flagCapteur[3][2];
};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////