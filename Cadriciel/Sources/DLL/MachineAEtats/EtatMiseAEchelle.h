#ifndef ETAT_MISE_A_ECHELLE_H
#define ETAT_MISE_A_ECHELLE_H

#include "EtatAbstrait.h"

class EtatMiseAEchelle : public EtatAbstrait
{
public:
	EtatMiseAEchelle();
	virtual ~EtatMiseAEchelle();
	virtual void effectuerOperation();
};








#endif