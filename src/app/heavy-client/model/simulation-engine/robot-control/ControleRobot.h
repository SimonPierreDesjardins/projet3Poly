///////////////////////////////////////////////////////////////////////////////
/// @file Comportement.h
/// @author Olivier St-Amour, Camille Gendreau
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
#include <mutex>
#include <vector>

#include "RobotPhysics.h"
#include "ComportementAbstrait.h"

class CommandeRobot;
class NoeudAbstrait;
class NoeudRobot;
class ArbreRendu;
class ControleurLumiere;
class ProfilUtilisateur;

namespace engine {
	class SimulationEngine;
}

namespace client_network {
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class ControleRobot
/// @brief Classe qui permet de contr�ler le robot. 
///
///        Cette classe permet de contr�ler le robot de fa�on automatique ou 
///		   de fa�on manuelle em recevant des commandes.
///		   
/// @author Olivier St-Amour, Camille Gendreau
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ControleRobot
{
	friend class ModeSimulation;
	friend class ModeTest;
	// Ceci nous permet de tester convenablement
	friend class ControleRobotTest;
	
public:
	ControleRobot() = default;
	ControleRobot(ArbreRendu* arbre, ProfilUtilisateur* profile);

	~ControleRobot();
	// Demande au robot de traiter une commande donn�e
	void traiterCommande(CommandeRobot* commande, bool provientUtilisateur);

	// Assigne le comportement correspondant � l'enum � l'IA du robot.
	void assignerComportement(TypeComportement nouveauComportement, std::wstring declencheur);

	// perme d'obtenir le noeud du robot. Souvent appel� par les comportements pour v�rifier des conditions.
	NoeudRobot* obtenirNoeud();

	// Fonctions permettant d'alterner entre les modes de contr�le
	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	// Peut-�tre rendre ceci priv�, l'ajustement de moteurs devrait se faire par commandes
	void assignerVitessesMoteurs(double vit_G, double vit_D);
    void ajouterVitessesMoteurs(double vit_G, double vit_D);

	// Permet aux comportements de savoir si une ligne est d�tect�e
	bool ligneDetectee();

	void assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur);

	void setEnPause(bool pause);
	bool getEnPause();

	bool getManuel();

private:

	bool isRunning_ = false;

	// d�finit si oui ou non le robot est en mode manuel
	bool manuel{ true };

	// d�finit si en mode debug
	bool enPause{ false };

	ArbreRendu* arbre_;
	NoeudAbstrait* table_;
	NoeudRobot* robot_;

	ProfilUtilisateur* profil_{ nullptr };
    ControleurLumiere* controleurLumiere_{ nullptr };
	client_network::MapSession* mapSession_{ nullptr };

	// pointeur vers le noeud du robot
	// Pointeur sur un profil
    // Pointeur sur le controleur de lumi�re.

	std::vector<std::unique_ptr<ComportementAbstrait>>* vecteurComportements_;

	RobotPhysics robotPhysic_;

	// Pointeur vers le comportement pr�sentement adopt� par le robot.
	ComportementAbstrait* comportement_;

	//Mutex servant � traiter l'acc�s au comportement du robot.
	std::mutex mutexComportement;

	// Pointeur vers le thread d'ex�cution du robot
	std::unique_ptr<std::thread> logiqueRobot;

	/*
	* Repr�sente les flags des capteurs, �vite de capter plusieurs fois dans le debugger
	* flagCapteur[X][Y]
	* X: 0 = droite, 1 = centre, 2 = gauche
	* Y: 0 = zone securitaire, 1 = zone danger */
	bool flagCapteur[3][2];

	// Joue le son appropri� du robot
	void jouerSonRobot(double vit_G, double vit_D);

	// Fonctions pour g�rer multithreading robot
	void initialiserBoucleRobot();
	void terminerBoucleRobot();
	void boucleInfinieLogiqueRobot();

	// Fonction qui verifie et effectue les changements en fonction des capteurs � obstacles
	void verifierCapteurs();

};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////