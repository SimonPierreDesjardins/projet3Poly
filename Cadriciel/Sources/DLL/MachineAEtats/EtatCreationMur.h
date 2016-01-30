///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_MUR_H
#define ETAT_CREATION_MUR_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"
#include <iostream>

class EtatCreationMur : public EtatAbstrait
{
public:
	EtatCreationMur();
	virtual ~EtatCreationMur();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int&y);
	virtual void gererToucheEchappe();
	virtual void gererEstSurTableConcret(bool positionEstSurTable);

private:
	bool enCreation_{ false };
	glm::dvec3 positionPremierClic_;
	NoeudAbstrait* mur_{ nullptr };

};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////