#ifndef ETAT_CREATION_LIGNE_H
#define ETAT_CREATION_LIGNE_H

#include "EtatAbstrait.h"

class EtatCreationLigneNoire : public EtatAbstrait
{
public:
	EtatCreationLigneNoire();
	virtual ~EtatCreationLigneNoire();
	virtual void effectuerOperation();
};








#endif