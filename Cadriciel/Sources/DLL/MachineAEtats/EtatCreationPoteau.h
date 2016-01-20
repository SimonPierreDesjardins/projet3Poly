#ifndef ETAT_CREATION_POTEAU_H
#define ETAT_CREATION_POTEAU_H

#include "EtatAbstrait.h"
#include <iostream>

class EtatCreationPoteau : public EtatAbstrait
{
public:
	EtatCreationPoteau();
	virtual ~EtatCreationPoteau();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);

	virtual void effectuerOperation();
};


#endif