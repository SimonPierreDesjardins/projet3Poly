///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_TEST_H
#define MODE_TEST_H

#include <memory>
#include <array>
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
/// @class ModeTest
/// @brief Classe qui représente le mode test de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode test
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

class ModeTest : public ModeAbstrait
{
private:
	std::unique_ptr<ControleRobot> controleRobot_;

	ProfilUtilisateur* profil_{ nullptr };
    AffichageTexte* affichageTexte_{ nullptr };

	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool lumiereAmbiante{ true };
	bool lumiereDirectionnelle{ true };
	bool lumiereSpot{ true };

	ControleurLumiere* controleurLumiere_{ nullptr };

	ArbreRenduINF2990* arbre_{ nullptr };
	VisiteurDetectionRobot visiteur_;

public:

	//Constructeur par défaut
	ModeTest();
	//Destructeur
	virtual ~ModeTest();
	
	void preChangementDeProfil();
	void postChangementDeProfil();

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void postAnimer();
	
protected:
	inline static std::array<char, 11>* getTouchesNonConfigurable();
};

std::array<char, 11>* ModeTest::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}
#endif /// MODE_TEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////