///////////////////////////////////////////////////////////////////////////
/// @file EtatRotation.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_ROTATION_H
#define ETAT_ROTATION_H

#include "EtatAbstrait.h"

class EtatRotation : public EtatAbstrait
{
public:
	EtatRotation();
	virtual ~EtatRotation();
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);

private:
	int dernierePositionY_;
	int positionInitialeY_;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////