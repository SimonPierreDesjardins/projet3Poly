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

#include <iostream> 

EtatCreationMur::EtatCreationMur()
{
	std::cout << "Creation de poteau" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationMur>();
	premierclic_ = false;
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
	glm::dvec3 positionVirutelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirutelle);
	positionPremierClic_ = positionVirutelle;
	visiteur_->assignerPositionRelative(positionVirutelle);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
	//FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(visiteur_.get()->getReferenceNoeud());
	
}

void EtatCreationMur::effectuerOperation()
{

}