///////////////////////////////////////////////////////////////////////////
/// @file EtatSelection.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatSelection.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "glm\glm.hpp"



EtatSelection::EtatSelection()
{
	std::cout << "Selection d'un object" << std::endl;
	visiteur_ = std::make_unique<VisiteurSelection>();
}

EtatSelection::~EtatSelection()
{

}


void EtatSelection::gererClicGaucheEnfonce(const int& x, const int& y)
{
	xEnfonce = x;
	yEnfonce = y;
}

void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
{
	int deltaX = 0, deltaY = 0;
	deltaX = x - xEnfonce;
	if (deltaX < 0)
	{
		deltaX = -deltaX;
	}
	deltaY = x - yEnfonce;
	if (deltaY < 0)
	{
		deltaY = -deltaY;
	}

	int moyenneX = 0, moyenneY = 0;
	moyenneX = (xEnfonce + x) / 2;
	moyenneY = (yEnfonce + y) / 2;

	if (deltaX < 3)
	{
		gererClicGauche(moyenneX, moyenneY);
	}
	else
	{
		gererDragGauche(xEnfonce, yEnfonce, x, y);
	}
}


void EtatSelection::gererClicGauche(const int& x, const int& y)
{
	glm::dvec3 positionRelative;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionRelative);
	visiteur_->assignerPositionRelative(positionRelative);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteur_.get());
}


void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	std::cout << "Drag gauche : " << xAvant << " " << yAvant << " a " << xApres << " " << yApres << std::endl;
}

void EtatSelection::effectuerOperation()
{

}