///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_LIGNE_H
#define ETAT_CREATION_LIGNE_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"
#include <iostream>
#include <vector>

class EtatCreationLigneNoire : public EtatAbstrait
{
public:
	EtatCreationLigneNoire();
	virtual ~EtatCreationLigneNoire();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererToucheEchappe();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererEstSurTableConcret(bool positionEstSurTable);

private:
	void calculerPositionCentreLigne();
	
	NoeudAbstrait* ligne_{ nullptr };
	NoeudAbstrait* segment_{ nullptr };
	bool enCreation_{ false };
	std::vector<glm::dvec3> positionsClic_;

};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////