///////////////////////////////////////////////////////////////////////////
/// @file EtatDuplication.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_DUPLICATION_H
#define ETAT_DUPLICATION_H

#include "EtatAbstrait.h"
#include "VisiteurDuplication.h"
#include "VisiteurVerificationObjets.h"


class EtatDuplication : public EtatAbstrait
{
public:
	EtatDuplication();
	virtual ~EtatDuplication();
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererEstSurTableConcret(bool positionEstSurTable);
	virtual void gererToucheEchappe();

protected:
	virtual void reinitialiser();

private:
	std::unique_ptr<VisiteurDuplication> visiteurDuplication_{ nullptr };
	std::unique_ptr<VisiteurVerificationObjets> visiteurVerificationObjets_{ nullptr };
	
	NoeudAbstrait* duplication_{ nullptr };
	bool enDuplication_{ false };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
