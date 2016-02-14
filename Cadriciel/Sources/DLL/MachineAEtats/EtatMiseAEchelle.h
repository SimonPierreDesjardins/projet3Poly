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
#include "VIsiteurMiseAjourQuad.h"
#include "VisiteurVerificationQuad.h"
#include "VisiteurMiseAEchelle.h"

class EtatMiseAEchelle : public EtatAbstrait
{
public:
	EtatMiseAEchelle();
	virtual ~EtatMiseAEchelle();
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);

protected:
	virtual void reinitialiser();

private:
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJourQuad_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	std::unique_ptr<VisiteurMiseAEchelle> visiteurMiseAEchelle_{ nullptr };

	double dernierePositionY_{ 0.0 };
	double positionInitialeY_{ 0.0 };
	double surplusMouvement_{ 0.0 };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
