#ifndef ETAT_DEPLACEMENT_H
#define ETAT_DEPLACEMENT_H

#include "EtatAbstrait.h"

class EtatDeplacement : public EtatAbstrait
{
public:
	EtatDeplacement();
	virtual ~EtatDeplacement();
	virtual void effectuerOperation();
};








#endif