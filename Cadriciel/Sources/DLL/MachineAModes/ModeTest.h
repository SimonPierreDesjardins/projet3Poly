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
#include "glm\glm.hpp"

#include "ModeAbstrait.h"
#include "ControleRobot.h"

class ProfilUtilisateur;

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
public:

	//Constructeur par défaut
	ModeTest();
	//Destructeur
	virtual ~ModeTest();
	
	void preChangementDeProfil();
	void postChangementDeProfil();

	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	//Gestion des entrées utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	
protected:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_;
};


#endif /// MODE_TEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////