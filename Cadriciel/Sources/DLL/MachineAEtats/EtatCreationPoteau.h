#ifndef ETAT_CREATION_POTEAU_H
#define ETAT_CREATION_POTEAU_H

#include "EtatAbstrait.h"

class EtatCreationPoteau : public EtatAbstrait
{
public:
	EtatCreationPoteau();
	virtual ~EtatCreationPoteau();
	virtual void effectuerOperation();
};








#endif