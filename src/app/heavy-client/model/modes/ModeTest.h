///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author Fr�d�ric Gr�goire
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

#include "OnlineMapMode.h"
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
/// @brief Classe qui repr�sente le mode test de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode test
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

class ModeTest : public OnlineMapMode
{
public:
	ModeTest(client_network::MapSession* mapSession);

	//Destructeur
	virtual ~ModeTest();
	
	void preChangementDeProfil();
	void postChangementDeProfil();

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	//Gestion des entr�es utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void postAnimer();

	bool obtenirModeEnPause();
	
protected:
	inline static std::array<char, 11>* getTouchesNonConfigurable();

private:
	//std::unique_ptr<ControleRobot> controleRobot_;

	ProfilUtilisateur* profil_{ nullptr };
    AffichageTexte* affichageTexte_{ nullptr };
	VisiteurDetectionRobot visiteur_;

	static std::array<char, 11> touchesNonConfigurable_;
    std::array<bool, 5> actionsAppuyees_;

	bool lumiereAmbiante{ true };
	bool lumiereDirectionnelle{ true };
	bool lumiereSpot{ true };
	bool modeEnPause{ false };

	ControleurLumiere* controleurLumiere_{ nullptr };

	ModeTest() = delete;
};

std::array<char, 11>* ModeTest::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}
#endif /// MODE_TEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////