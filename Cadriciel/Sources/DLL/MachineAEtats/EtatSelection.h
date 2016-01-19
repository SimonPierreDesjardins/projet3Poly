#ifndef ETAT_SELECTION_H
#define ETAT_SELECTION_H

#include "EtatAbstrait.h"

class EtatSelection : public EtatAbstrait
{
public:
	EtatSelection();
	virtual ~EtatSelection();
	virtual void effectuerOperation();
};








#endif