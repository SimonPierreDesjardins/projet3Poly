///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.h
/// @author Frédéric Grégoire
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
#include "ModeAbstrait.h"
#include "ControleRobot.h"
#include "FacadeModele.h"
#include "VisiteurDetectionRobot.h"
#include <unordered_map>
#include <array>

class ProfilUtilisateur;
class AffichageTexte;
class ControleurLumiere;

//////////////////////////////////////////////////////////////////////////
/// @class ModeSimulation
/// @brief Classe qui représente le mode simulation de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode simulation
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeSimulation : public ModeAbstrait 
{
private:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_{ nullptr };
	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool lumiereAmbiante { true };
	bool lumiereDirectionnelle { true };
	bool lumiereSpot { true };

	VisiteurDetectionRobot visiteur_;

    AffichageTexte* affichageTexte_{ nullptr };

	ControleurLumiere* controleurLumiere_{ nullptr };

	ArbreRenduINF2990* arbre_{ nullptr };

	bool modeEnPause{ false };

public:
	//Constructeur par défaut
	ModeSimulation();
	//Destructeur
	virtual ~ModeSimulation();
	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	void preChangementDeProfil();
	void postChangementDeProfil();

	virtual void postAnimer();

	inline static std::array<char, 11>* getTouchesNonConfigurable();

	bool obtenirModeEnPause();
};

std::array<char, 11>* ModeSimulation::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}

#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////