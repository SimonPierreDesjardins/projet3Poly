///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationPoteau.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationPoteau.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "glm\glm.hpp"

#include <iostream> 

EtatCreationPoteau::EtatCreationPoteau()
{
	std::cout << "Creation de poteau" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationPoteau>();
}




EtatCreationPoteau::~EtatCreationPoteau()
{

}

void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
{
}

void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
{
	if (!curseurEstSurTable_) return;
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	visiteur_->assignerPositionRelative(positionVirtuelle);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
}

void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
{
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	gererEstSurTable(positionVirtuelle);
}

void EtatCreationPoteau::gererEstSurTableConcret(bool positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		assignerSymbolePointeur(curseurEstSurTable_);
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		assignerSymbolePointeur(curseurEstSurTable_);
	}
}