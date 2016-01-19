#ifndef ETAT_CREATION_MUR_H
#define ETAT_CREATION_MUR_H

#include "EtatAbstrait.h"

class EtatCreationMur : public EtatAbstrait
{
public:
	EtatCreationMur();
	virtual ~EtatCreationMur();
	virtual void effectuerOperation();
};








#endif