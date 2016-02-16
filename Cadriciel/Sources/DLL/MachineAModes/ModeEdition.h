///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.h
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_EDITION_H
#define MODE_EDITION_H

#include "ModeAbstrait.h"
#include "VisiteurAbstrait.h"
#include "VisiteurSuppression.h"
#include <memory>
#include "glm\glm.hpp"

//////////////////////////////////////////////////////////////////////////
/// @class ModeEdition
/// @brief Classe qui représente le mode edition de notre machine à modes
///
///        Cette classe s'occupe d'implémenter les fonctions du mode edition

/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeEdition : public ModeAbstrait
{
public:

	//Constructeur par défaut
	ModeEdition();
	//Destructeur
	virtual ~ModeEdition();

	
	//Gestion des différentes touches et de leur effet selon le mode choisi
	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererToucheEchappe();

	virtual void gererToucheC();
	virtual void gererToucheD();
	virtual void gererToucheE();
	virtual void gererToucheR();
	virtual void gererToucheS();
	virtual void gererToucheT();
	virtual void gererToucheW();
	virtual void gererToucheZ();

	virtual void gererToucheCTRLavecS();
	virtual void gererToucheCTRLavecN();
	virtual void gererToucheCTRLavecO();

	virtual void gererTouche1();
	virtual void gererTouche2();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	//Gestion de touches modificatrices
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererToucheAltEnfoncee();
	virtual void gererToucheAltRelachee();

	// Gestion de la souris
	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);
	virtual void gererMoletteSouris(const int & delta);

	virtual void gererToucheSupprimer();

	//Gestion du système de chargement et de sauvegarde
	virtual void sauvegarder();
	virtual void charger();

protected:

	//Visiteur pour la suppression d'un noeud
	std::unique_ptr<VisiteurSuppression> visiteurSuppression_;

	//Ancienne position en X et Y de la souris
	int ancienSourisX_{ 0 };
	int ancienSourisY_{ 0 };

};


#endif /// MODE_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////