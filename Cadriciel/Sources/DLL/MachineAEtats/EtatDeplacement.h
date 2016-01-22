///////////////////////////////////////////////////////////////////////////
/// @file EtatDeplacement.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

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