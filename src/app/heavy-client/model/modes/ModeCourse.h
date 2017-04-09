///////////////////////////////////////////////////////////////////////////
/// @file ModeCourse.h
/// @author Simon-Pierre Desjardins
/// @date 2016-03-29
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_COURSE_H
#define MODE_COURSE_H

#include <memory>
#include "glm\glm.hpp"
#include "ModeAbstrait.h"
#include "ControleRobot.h"
#include "FacadeModele.h"
#include "VisiteurDetectionRobot.h"
#include <unordered_map>
#include <array>
#include "Minuterie.h"

class ProfilUtilisateur;
class AffichageTexte;
class ControleurLumiere;

//////////////////////////////////////////////////////////////////////////
/// @class ModeCourse
/// @brief Classe qui représente le mode course de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode course
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeCourse : public ModeAbstrait 
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

	Minuterie timerAvantDecompte;
	Minuterie decompteAvantDepart;
	Minuterie timerAvantFin;

	bool finDecompte = false;
	bool faitReinitialiserChrono = false;

public:
	//Constructeur par défaut
	ModeCourse();
	//Destructeur
	virtual ~ModeCourse();
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

std::array<char, 11>* ModeCourse::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}

#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////