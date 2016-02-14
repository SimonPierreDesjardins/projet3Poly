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
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "AideGl.h"
#include "glm\glm.hpp"


EtatSelection::EtatSelection()
{
	visiteurSelection_ = std::make_unique<VisiteurSelection>();
	visiteurMiseAJourQuad_ = std::make_unique<VisiteurMiseAJourQuad>();
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	vue_ = FacadeModele::obtenirInstance()->obtenirVue();
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
		gererClicGauche((anchor.x + currentPosition_.x) / 2, (anchor.y + currentPosition_.y) / 2);
	}
}

void EtatSelection::gererMouvementSouris(const int & x, const int& y){

	if (clicGaucheEnfonce_){
		// Initialisation du rectangle elastique
		if (estClickDrag()){

			if (dessineRectangle)
				aidegl::mettreAJourRectangleElastique(anchor, currentPosition_, glm::ivec2(x, y));
			else{
				aidegl::initialiserRectangleElastique(anchor);
				FacadeModele::obtenirInstance()->stopAffichage();
				dessineRectangle = true;
				//Placer notre nouveau rectangle initial, assure fonctionnement de mise à jour
				aidegl::mettreAJourRectangleElastique(anchor, anchor, glm::ivec2(x, y));
			}
		}
		//TODO Arrêter de dessiner un rectangle si on quite le clickdrag
	}
	EtatAbstrait::gererMouvementSouris(x, y);

}


void EtatSelection::gererClicGauche(const int& x, const int& y)
{
	visiteurSelection_->assignerEstDrag(false);
	glm::dvec3 positionRelative = { 0.0, 0.0, 0.0 };
	
	if (vue_ != nullptr)
	{
		vue_->convertirClotureAVirtuelle(x, y, positionRelative);
	}
	
	visiteurSelection_->assignerPositionRelative(positionRelative);
	
	if (arbre_ != nullptr)
	{
		arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
		arbre_->accepterVisiteur(visiteurSelection_.get());
	}
}


void EtatSelection::gererDragGauche(const int& xAvant, const int& yAvant, const int& xApres, const int& yApres)
{
	visiteurSelection_->assignerEstDrag(true);
	glm::dvec3 positionRelativeAvant, positionRelativeApres;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xAvant, yAvant, positionRelativeAvant);
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xApres, yApres, positionRelativeApres);
	visiteurSelection_->assignerPositionRectElast(positionRelativeAvant, positionRelativeApres);
	
	arbre_->accepterVisiteur(visiteurMiseAJourQuad_.get());
	arbre_->accepterVisiteur(visiteurSelection_.get());
}

void EtatSelection::gererToucheControlEnfoncee()
{
	visiteurSelection_->assignerControl(true);
}

void EtatSelection::gererToucheControlRelachee()
{
	visiteurSelection_->assignerControl(false);
}