///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationMur.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

EtatCreationMur::EtatCreationMur()
{
	std::cout << "Creation de poteau" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationMur>();
	estPremierClic_ = false;
}

EtatCreationMur::~EtatCreationMur()
{

}

void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
{
	//Deuxieme clic
	if (estPremierClic_)
	{
		estPremierClic_ = false;
	}
	//Premier clic
	else
	{
		estPremierClic_ = true;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		visiteur_->assignerPositionRelative(positionPremierClic_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());

		referenceNoeud_ = visiteur_.get()->obtenirReferenceNoeud();
	}
	
}

void EtatCreationMur::gererToucheEchappe()
{
	if (estPremierClic_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(referenceNoeud_);
		estPremierClic_ = false;
	}
}

void EtatCreationMur::gererMouvementSouris(const int& x, const int&y)
{
	glm::dvec3 positionVirtuelle;
	glm::dvec3 nouvellePosition;
	float angle = 0;
	double distance = 0;

	if (estPremierClic_)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionVirtuelle);
		referenceNoeud_->assignerAngleRotation(angle);
		distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionVirtuelle);
		referenceNoeud_->assignerFacteurDimension(distance);
		nouvellePosition = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionVirtuelle);
		referenceNoeud_->assignerPositionRelative(nouvellePosition);
	}
}

void EtatCreationMur::effectuerOperation()
{

}