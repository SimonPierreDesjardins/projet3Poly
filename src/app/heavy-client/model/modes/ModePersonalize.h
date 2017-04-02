///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author Frédéric Grégoire
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
/// @brief Classe qui représente le mode test de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode test
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

class ModePersonalize : public ModeAbstrait
{
public:
	//Constructeur par défaut
	ModePersonalize();

	//Destructeur
	virtual ~ModePersonalize();

	void gererMoletteSouris(const int & delta);

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	void creerControleRobot();

private:
	ProfilUtilisateur* profil_{ nullptr };

	ArbreRendu* tree_{ nullptr };

	bool lumiereAmbiante{ true };
	bool lumiereDirectionnelle{ true };
	bool lumiereSpot{ true };

	ControleurLumiere* controleurLumiere_{ nullptr };

};

#endif /// MODE_PERSONALIZE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////