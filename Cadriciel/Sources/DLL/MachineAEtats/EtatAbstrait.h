///////////////////////////////////////////////////////////////////////////
/// @file EtatAbstrait.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_ABSTRAIT_H
#define ETAT_ABSTRAIT_H

#include <memory>
#include "VisiteurAbstrait.h"
#include "glm\glm.hpp"

class EtatAbstrait
{
public:
	EtatAbstrait();
	virtual ~EtatAbstrait();

	// Gestion de la souris
	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);
	virtual void gererMoletteSouris(const int & delta);

	// Gestion de touches
	virtual void gererToucheEchappe();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererTouchePlus();
	virtual void gererToucheMoins();
	virtual void gererToucheAltEnfoncee();
	virtual void gererToucheAltRelachee();

protected:
	std::unique_ptr<VisiteurAbstrait> visiteur_;

	bool toucheCtrlEnfonce_{ false };
	bool toucheAltEnfonce_{ false };
	bool enCreation_{ false };
	bool clicGaucheEnfonce_{false};
	bool clicDroitEnfonce_{false};
	int ancienX_;
	int ancienY_;
	bool estPremierClic_{ false };

	glm::dvec3 positionPremierClic_;
	glm::dvec3 positionDeuxiemeClic_;

};

#endif