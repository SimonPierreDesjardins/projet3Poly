#ifndef ETAT_ROTATION_H
#define ETAT_ROTATION_H

#include "EtatAbstrait.h"

class EtatRotation : public EtatAbstrait
{
public:
	EtatRotation();
	virtual ~EtatRotation();
	virtual void effectuerOperation();
};








#endif