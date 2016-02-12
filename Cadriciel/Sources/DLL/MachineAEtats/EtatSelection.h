///////////////////////////////////////////////////////////////////////////
/// @file EtatSelection.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_SELECTION_H
#define ETAT_SELECTION_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"

class EtatSelection : public EtatAbstrait
{
public:
	EtatSelection();
	virtual ~EtatSelection();

	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);

	void gererClicGauche(const int& x, const int& y);

	void gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres);

	void gererToucheControlEnfoncee();
	void gererToucheControlRelachee();

private:
	bool dessineRectangle{ false };

private : 
	std::unique_ptr<VisiteurSelection> visiteurSelection_;
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
