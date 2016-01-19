#ifndef ETAT_Duplication_H
#define ETAT_Duplication_H

#include "EtatAbstrait.h"

class EtatDuplication : public EtatAbstrait
{
public:
	EtatDuplication();
	virtual ~EtatDuplication();
	virtual void effectuerOperation();
};








#endif