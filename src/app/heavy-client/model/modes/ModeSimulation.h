///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_SIMULATION_H
#define MODE_SIMULATION_H

#include <memory>
#include "glm\glm.hpp"
#include "OnlineMapMode.h"
#include "ControleRobot.h"
#include "VisiteurDetectionRobot.h"
#include <unordered_map>
#include <array>

class ProfilUtilisateur;
class AffichageTexte;
class ControleurLumiere;

namespace engine {
	class SimulationEngine;
}

//////////////////////////////////////////////////////////////////////////
/// @class ModeSimulation
/// @brief Classe qui repr�sente le mode simulation de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode simulation
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeSimulation : public OnlineMapMode
{
public:
	ModeSimulation(engine::SimulationEngine* engine, ProfilUtilisateur* profil, client_network::MapSession* session);

	//Destructeur
	virtual ~ModeSimulation();
	//Gestion des entr�es utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	void preChangementDeProfil();
	void postChangementDeProfil();

	virtual void postAnimer();

	inline static std::array<char, 11>* getTouchesNonConfigurable();

private:
	ControleRobot controleRobot_;
	ProfilUtilisateur* profil_{ nullptr };
	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool modeEnPause = false;
	bool lumiereAmbiante { true };
	bool lumiereDirectionnelle { true };
	bool lumiereSpot { true };

    AffichageTexte* affichageTexte_{ nullptr };
	ControleurLumiere* controleurLumiere_{ nullptr };
	
	//Constructeur par d�faut
	bool obtenirModeEnPause();
	ModeSimulation() = delete;
};

std::array<char, 11>* ModeSimulation::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}

#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////