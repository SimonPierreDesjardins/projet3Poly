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
#include "VisiteurVerificationQuad.h"


class EtatDuplication : public EtatAbstrait
{
public:
	EtatDuplication();
	virtual ~EtatDuplication();
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererEstSurTableConcret(bool positionEstSurTable);

private:
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJourQuad_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	std::unique_ptr<VisiteurDuplication> visiteurDuplication_{ nullptr };

	NoeudAbstrait* duplication_{ nullptr };
	bool enDuplication_{ false };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
