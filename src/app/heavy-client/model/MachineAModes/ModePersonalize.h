///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_PERSONALIZE_H
#define MODE_PERSONALIZE_H

#include <memory>
#include <array>
#include "glm\glm.hpp"

#include "ModeAbstrait.h"
#include "ControleRobot.h"
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

class ModePersonalize : public ModeAbstrait
{
private:
	ProfilUtilisateur* profil_{ nullptr };

	bool lumiereAmbiante{ true };
	bool lumiereDirectionnelle{ true };
	bool lumiereSpot{ true };

	ControleurLumiere* controleurLumiere_{ nullptr };

public:

	//Constructeur par d�faut
	ModePersonalize();
	//Destructeur
	virtual ~ModePersonalize();

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	//Gestion des entr�es utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	
};

#endif /// MODE_PERSONALIZE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////