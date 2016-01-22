///////////////////////////////////////////////////////////////////////////
/// @file EtatDuplication.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

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