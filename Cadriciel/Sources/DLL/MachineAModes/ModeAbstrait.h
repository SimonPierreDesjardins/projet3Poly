///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.h
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_ABSTRAIT_H
#define MODE_ABSTRAIT_H

#include <memory>
#include "glm\glm.hpp"

enum Mode
{
	MENU_PRINCIPAL,
	SIMULATION,
	EDITION,
	CONFIGURE,
	TEST
};

class ModeAbstrait
{
public:
	ModeAbstrait();
	virtual ~ModeAbstrait();

	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererToucheEchappe();

	virtual void gererToucheB();
	virtual void gererToucheC();
	virtual void gererToucheD();
	virtual void gererToucheE();
	virtual void gererToucheJ();
	virtual void gererToucheK();
	virtual void gererToucheL();
	virtual void gererToucheR();
	virtual void gererToucheS();
	virtual void gererToucheT();
	virtual void gererToucheZ();

	virtual void gererToucheCTRLavecS();
	virtual void gererToucheCTRLavecN();
	virtual void gererToucheCTRLavecO();

	virtual void gererTouche1();
	virtual void gererTouche2();
	virtual void gererTouche3();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	virtual void gererBarreDespacement();

	virtual void gererToucheArriere();

	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();

	inline int obtenirTypeMode();

protected:
	int typeMode_;

};

inline int ModeAbstrait::obtenirTypeMode()
{
	return typeMode_;
}

#endif /// MODE_ABSTRAIT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////