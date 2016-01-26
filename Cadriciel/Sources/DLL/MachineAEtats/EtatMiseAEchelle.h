///////////////////////////////////////////////////////////////////////////
/// @file EtatMiseAEchelle.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

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