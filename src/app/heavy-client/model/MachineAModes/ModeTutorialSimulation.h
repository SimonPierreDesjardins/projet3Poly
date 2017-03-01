///////////////////////////////////////////////////////////////////////////
/// @file ModeTutorialSimulation.h
/// @author Frédéric Grégoire
/// @date 2017-03-01
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_TUTORIAL_SIMULATION_H
#define MODE_TUTORIAL_SIMULATION_H

#include <memory>
#include "glm\glm.hpp"
#include "ModeAbstrait.h"
#include "ControleRobot.h"
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
///////////////////////////////////////////////////////////////////////////
class ModeTutorialSimulation : public ModeAbstrait 
{
private:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_{ nullptr };
	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool lumiereAmbiante { true };
	bool lumiereDirectionnelle { true };
	bool lumiereSpot { true };

    AffichageTexte* affichageTexte_{ nullptr };

	ControleurLumiere* controleurLumiere_{ nullptr };

public:
	//Constructeur par défaut
	ModeTutorialSimulation();
	//Destructeur
	virtual ~ModeTutorialSimulation();
	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	void preChangementDeProfil();
	void postChangementDeProfil();

	inline static std::array<char, 11>* getTouchesNonConfigurable();
};

std::array<char, 11>* ModeTutorialSimulation::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}

#endif /// MODE_TUTORIAL_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////