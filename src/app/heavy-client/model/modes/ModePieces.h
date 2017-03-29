///////////////////////////////////////////////////////////////////////////
/// @file ModePieces.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_PIECES_H
#define MODE_PIECES_H

#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include "glm\glm.hpp"
#include "ModeAbstrait.h"
#include "ControleRobot.h"
#include <unordered_map>
#include <array>
#include "FacadeModele.h"
#include "Minuterie.h"

class ProfilUtilisateur;
class AffichageTexte;
class ControleurLumiere;

//////////////////////////////////////////////////////////////////////////
/// @class ModePieces
/// @brief Classe qui représente le mode de jeu pieces de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode pieces
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModePieces : public ModeAbstrait
{
private:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_{ nullptr };
	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool lumiereAmbiante { true };
	bool lumiereDirectionnelle { true };
	bool lumiereSpot { true };

	std::shared_ptr<NoeudAbstrait> noeudCoinCourant;

	ArbreRenduINF2990* arbre_{nullptr};
	NoeudAbstrait* table_{ nullptr };
    AffichageTexte* affichageTexte_{ nullptr };
	glm::dvec3 positionNoeudCourant;
	ControleurLumiere* controleurLumiere_{ nullptr };

	bool modeEnPause{ false };
	VisiteurDetectionRobot visiteur_;

	Minuterie minuterie_;

	std::thread th;

	bool objectsReadyToSpawn{ false };

	std::vector <std::shared_ptr <NoeudAbstrait>> objectsToSpawn;

	std::mutex spawnLock;

public:
	//Constructeur par défaut
	ModePieces();
	//Destructeur
	virtual ~ModePieces();
	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	void preChangementDeProfil();
	void postChangementDeProfil();

	glm::dvec3 genererPositionCoin();

	virtual void postAnimer();

	inline static std::array<char, 11>* getTouchesNonConfigurable();

	bool obtenirModeEnPause();
	void creerPieces();

	void startThread();

	void spawnObjects();
};

std::array<char, 11>* ModePieces::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}

#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////