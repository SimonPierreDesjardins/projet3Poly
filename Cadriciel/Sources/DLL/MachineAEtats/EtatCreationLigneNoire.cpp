///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationLigneNoire.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"

#include <iostream> 

EtatCreationLigneNoire::EtatCreationLigneNoire()
{
	std::cout << "Creation de poteau" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationLigne>();
}

EtatCreationLigneNoire::~EtatCreationLigneNoire()
{

}

void EtatCreationLigneNoire::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationLigneNoire::gererClicGaucheRelache(const int& x, const int& y)
{
	
	glm::dvec3 positionRelative;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionRelative);
	visiteur_->assignerPositionRelative(positionRelative);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
	
	/*
	if (estPremierClic_)
	{
		estPremierClic_ = false;
	}
	else
	{
		estPremierClic_ = true;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);	
	}
	*/
}


void EtatCreationLigneNoire::gererMouvementSouris(const int& x, const int& y)
{
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	double dx = 0;
	double dy = 0;
	float angle = 0;
	if (estPremierClic_)
	{
		dx = positionVirtuelle[0] - positionPremierClic_[0];
		dy = positionVirtuelle[1] - positionPremierClic_[1];
		angle = calculerAngleRotation(dx, dy);
	}
	//std::cout << "x: " << positionVirtuelle[0] << " y: " << positionVirtuelle[1] << " z: " << positionVirtuelle[2] << std::endl;
	std::cout << "dx: " << dx << " dy: " << dy << std::endl;
	std::cout << "angle: " << angle << std::endl;
}

void EtatCreationLigneNoire::effectuerOperation()
{

}