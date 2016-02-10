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
#include "AideGl.h"
#include "glm\glm.hpp"



EtatSelection::EtatSelection()
{
	std::cout << "Selection d'un object" << std::endl;
	visiteurSelection_ = std::make_unique<VisiteurSelection>();
}

EtatSelection::~EtatSelection()
{

}

void EtatSelection::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);

	if (dessineRectangle){
		FacadeModele::obtenirInstance()->continuerAffichage();

		aidegl::terminerRectangleElastique(anchor, glm::ivec2(x, y));

		dessineRectangle = false;
	}

	if (estClickDrag())
	{
		gererDragGauche(xEnfonce_, yEnfonce_, x, y);
	}
	else
	{
		gererClicGauche(std::abs(anchor.x - currentPosition.x) / 2, std::abs(anchor.y - currentPosition.y) / 2);
	}
}

void EtatSelection::gererMouvementSouris(const int & x, const int& y){

	if (clicGaucheEnfonce_){
		if (estClickDrag()){
			if (dessineRectangle)
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition, glm::ivec2(x, y));
			else{
				aidegl::initialiserRectangleElastique(anchor);
				// redessiner le rectangle
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
			}
		}
	}
	EtatAbstrait::gererMouvementSouris(x, y);

}


void EtatSelection::gererClicGauche(const int& x, const int& y)
{
	glm::dvec3 positionRelative;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionRelative);
	visiteurSelection_->assignerPositionRelative(positionRelative);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteurSelection_.get());
}


void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	std::cout << "Drag gauche : " << xAvant << " " << yAvant << " a " << xApres << " " << yApres << std::endl;
}

void EtatSelection::gererToucheControlEnfoncee()
{
	visiteurSelection_->assignerControl(true);
}

void EtatSelection::gererToucheControlRelachee()
{
	visiteurSelection_->assignerControl(false);
}