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

class ModeEdition : public ModeAbstrait
{
public:
	ModeEdition();
	virtual ~ModeEdition();

	

	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererToucheEchappe();

	virtual void gererToucheC();
	virtual void gererToucheD();
	virtual void gererToucheE();
	virtual void gererToucheR();
	virtual void gererToucheS();
	virtual void gererToucheT();
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

	virtual void sauvegarder();
	virtual void charger();

protected:
	std::unique_ptr<VisiteurSuppression> visiteurSuppression_;

	int ancienSourisX_;
	int ancienSourisY_;

};


#endif /// MODE_EDITION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////