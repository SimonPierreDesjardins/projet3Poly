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
	typeEtat_ = SELECTION;
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
		gererDragGauche(anchor.x, anchor.y, x, y);
	}
	else
	{
		gererClicGauche((anchor.x + currentPosition.x) / 2, (anchor.y + currentPosition.y) / 2);
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
	visiteurSelection_->assignerEstDrag(false);
	glm::dvec3 positionRelative;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionRelative);
	visiteurSelection_->assignerPositionRelative(positionRelative);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurSelection_.get());
}


void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	visiteurSelection_->assignerEstDrag(true);
	std::cout << "Drag gauche : " << xAvant << " " << yAvant << " a " << xApres << " " << yApres << std::endl;
	glm::dvec3 positionRelativeAvant, positionRelativeApres;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xAvant, yAvant, positionRelativeAvant);
	visiteurSelection_->assignerPositionRelativeAvant(positionRelativeAvant);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xApres, yApres, positionRelativeApres);
	visiteurSelection_->assignerPositionRelativeApres(positionRelativeApres);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurSelection_.get());
}

void EtatSelection::gererToucheControlEnfoncee()
{
	visiteurSelection_->assignerControl(true);
}

void EtatSelection::gererToucheControlRelachee()
{
	visiteurSelection_->assignerControl(false);
}