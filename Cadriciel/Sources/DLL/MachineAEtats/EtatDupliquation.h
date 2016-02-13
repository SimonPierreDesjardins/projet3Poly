///////////////////////////////////////////////////////////////////////////
/// @file EtatDupliquation.h
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
#include "VisiteurDupliquation.h"
#include "VisiteurVerificationQuad.h"


class EtatDupliquation : public EtatAbstrait
{
public:
	EtatDupliquation();
	virtual ~EtatDupliquation();
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererEstSurTableConcret(bool positionEstSurTable);
	virtual void gererToucheEchappe();

protected:
	virtual void reinitialiser();

private:
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJourQuad_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	std::unique_ptr<VisiteurDupliquation> visiteurDupliquation_{ nullptr };

	NoeudAbstrait* duplication_{ nullptr };
	bool enDuplication_{ false };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
